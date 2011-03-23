require 'rubygems'
require 'mysql'
require 'mongrel'
require 'feynman'
require 'getoptlong'
require 'digest/md5'
require 'rdoc/usage'

# For the love of monkey patching we have some necessary evils that we
# have chosen to do in this manner because they are harmless additions
# to the class but go a long way in our server..
module Mongrel
  module Const
    # We use this constant for responding with CSV files.
    CONTENT_DISPOSITION = 'Content-disposition'

    # HTTP request params hash keys.
    SERVER_NAME = 'SERVER_NAME'
    SERVER_PORT = 'SERVER_PORT'
  end

  # We like our logger more than theirs.
  class Configurator
    # This method overrides the default and uses the server's logger so
    # that all messaging in this file is formatted in the same manner.
    def log( msg )
      FeynmanServer.log( msg )
    end
  end
end

# == Synopsis
# 
# The Feynman Server is a web server that has the specific capability of
# executing simulations built using the Feyman Simulation Framework.
# 
# == Usage
# 
# ruby feynman_server.rb [start|stop] [options]
#
# [<tt>-p, --port</tt>]         - Which port to bind to
# [<tt>-d, --daemonize</tt>]    - Run daemonized in the background
# [<tt>-l, --log</tt>]          - Where to write the log messages
# [<tt>-P, --pid</tt>]          - Where to write the PID file
# [<tt>-a, --address ADDR</tt>] - Address to bind to (default: localhost)
# [<tt>-s, --storage</tt>]      - Storage location (default: /usr/local/feynman/storage)
# [<tt>-C, --config PATH</tt>]  - Use a config file to specify server options
# [<tt>-f, --force</tt>]        - Issue KILL instead of TERM (specific to stop)
#
# ==== Examples
#
#   ruby feynman_server.rb start -C /usr/local/webservers/feynman/config/
# 
# == Author
# Wes Bailey, wes@verticalresponse.com
module FeynmanServer
  # For now this module provides methods for accessing assets that are stored
  # in the user's media directory.  This can include anything from source code
  # to data files.
  #
  # *Note*: In the future we might consider swapping this out to use {Amazon S3}[http://aws.amazon.com/s3].
  module Storage
    # This trick enables this default to be overridden at server startup.
    DIR = {
      :home => '/usr/local/storage/feynman_server',
    }

    # Users are identified by a hash to the server which is used to create an
    # even distribution of directories that are available to them for data and
    # library file access.
    module User
      # For the documentation in these methods assume the following for examples:
      #
      #   Storage::DIR[:home] = /usr/local/storage/feynman_server
      #
      # and the user's hash is <em>2a5ed0ff2f45</em>
      module Dir
        # Defines the location to the user's home directory.
        #
        # [+hash+] - The user's identifying hash.
        #
        # ====Example
        #     /usr/local/storage/feynman_server/simulations/2/a/2a5ed0ff2f45
        def self.home( hash )
          [ Storage::DIR[:home], hash[0,1], hash[1,1], hash[2,1], hash ]
        end

        # Defines the location of the user's lib directory where all Feynman Simulation
        # Framework code will live to run a simulation.
        #
        # [+hash+] - The user's identifying hash.
        #
        # ====Example
        #     /usr/local/storage/feynman_server/simulations/2/a/2a5ed0ff2f45/lib
        def self.lib( hash )
          [ self.home( hash ), 'lib' ].join( '/' )
        end

        # Defines the location where the data for the executed simulation will live
        # if a filename has been supplied as part of request.
        #
        # [+hash+] - The user's identifying hash.
        #
        # ====Example
        #     /usr/local/storage/feynman_server/simulations/2/a/2a5ed0ff2f45/data
        def self.data( hash )
          [ self.home( hash ), 'data' ].join( '/' )
        end
      end

      # For the documentation in these methods assume the following for examples:
      #
      #   Storage::DIR[:home] = /usr/local/storage/feynman_server
      #
      # and the user's hash is <em>2a5ed0ff2f45</em>
      module File
        # The file in their storage that contains the results of the simulation run.
        #
        # [_hash_]     - The user's hash value
        # [_filename_] - The name of the file to store the data of a simulation run in.
        #
        # ====Example
        #   /usr/local/storage/feynman_server/simulations/2/a/2a5ed0ff2f45/data/run2.csv
        def self.data( hash, filename )
          [ Storage::User::Dir.data( hash ), filename ].join( '/' )
        end

        # Points the module file the user has defined for the simulation they want to run.
        #
        # [_hash_]     - The user's hash value
        # [_filename_] - The filename of the module containing the simulation definition.
        #
        # ====Example
        #   /usr/local/storage/feynman_server/simulations/2/a/2a5ed0ff2f45/lib/projectile_motion
        def self.simulation( hash, filename )
          [ Storage::User::Dir.lib( hash ), filename ].join( '/' )
        end
      end
    end
  end

  class ServerHandler < Mongrel::HttpHandler
    def process( request, response )
      # I think this is where I want to put the code for logging the handler invocation
      # into the database.
    end

    # This is just here because I want to be lazy and just type log in the handlers.
    def log( message )
      FeynmanServer.log( message )
    end

    # A wrapper for response.start that can be used for simple responses
    def respond( response, status, message )
      response.start( status ) { |head, buffer| buffer.write( message ) }
    end

    def parse_params( request )
      hash = request.body.read.split( '&' ).inject( {} ) { |h,t| k,v = t.split( '=' ); h.merge( { k.to_sym => v } ) }
      raise( Exception, 'Unable to parse request parameters' ) unless request.body.eof?
      hash
    end
  rescue Exception => e
    # Log this problem in the database.
    raise( e, e.message )
  else
    # Record success in the database for the current invocation
  end

  class AuthenticateHandler < ServerHandler
    def process( request, response )
      log '-- Authentication request start --'

      credentials = parse_params( request )

      # In the future we will invoke a call on the authentication server to
      # verify the supplied credentials.
      unless credentials[:password].eql?( 'test' )
        log "Invalid User Credentials: username = #{credentials[:username]}"
        respond( response, 403, 'Invalid User Credentials' )
        log '-- request end --'
        return
      end

      # This will become the user's actual record id.
      user_id = rand( "1e#{rand( 8 )}".to_f )

      token = Digest::MD5.hexdigest( Time.now.to_i.to_s )

      sql =<<-SQL
        insert into fs_session
        ( token
        , created_by
        , create_date
        , server_host
        , server_port
        , client_ip_address
        ) values
        ( '#{token}'
        , '#{user_id}'
        , now()
        , '#{request.params[Mongrel::Const::SERVER_NAME]}'
        , '#{request.params[Mongrel::Const::SERVER_PORT]}'
        , '#{request.params[Mongrel::Const::REMOTE_ADDR]}'
        );
      SQL

      conn = Mysql.new( 'localhost', 'feynman', 'feynman', 'fs' )

      begin
        conn.query( sql )
      rescue Exception => e
        log e.message
        respond( response, 500, e.message )
      else
        log token
        respond( response, 200, token )
      end

      log '-- request end --'
    end
  end

  class SimulationHandler < ServerHandler
    def process( request, response )
      errors, run = [], {}

      log '-- Simulation request start --'

      # Simply parse the request.
      #ignore_me, run[:user_hash], run[:module_filename], run[:data_filename] = request.params[Mongrel::Const::PATH_INFO].split( '/' )

      run = parse_params( request )

      # Validate the required request parameters.
      run.each_key do |k|
        log "#{k.to_s}: #{run[k]}"

        case k
          when :user_hash, :module_filename
            errors << "#{k.to_s} must be defined in the request." if run[k].nil?
        end
      end

      # This may not be a valid path, but it will never fail.  Also note that we 
      # put it first in the list because at the end of the simulation we remove it
      # to prevent polluting the server's load path after processing a lot of
      # simulation requests.
      $LOAD_PATH.unshift( Storage::User::Dir.lib( run[:user_hash] ) )

      log "Added #{Storage::User::Dir.lib( run[:user_hash] )} to $LOAD_PATH"

      begin
        require Storage::User::File.simulation( run[:user_hash], run[:module_filename] )
      rescue LoadError => e
        log e.message
        errors << e.message
      end

      unless errors.empty?
        respond( response, 412, errors.join( "\n" ) )
        log '-- request end --'
        return
      end

      # For now we are adopting the convention that the module's filename can be used
      # to derive the class name it contains using the simple rule:
      #
      # projectile_motion => ProjectileMotion
      classname = run[:module_filename].split( '_' ).map { |v| v.capitalize }.join

      # Through the cleverness of the simulation framework we can use this procedure
      # to run the specified simulation.  Example: invoker.call => ProjectileMotion.execute
      invoker = lambda { Class.const_get( classname ).send( 'execute' ) }

      # The simulation framework uses STDOUT as well so lets ensure that we write to the
      # correct output pipe for the simulation but then have the ability to have the
      # server write to the correct pipe after it has completed.
      restore_stdout_to = $stdout.clone

      # NOTE: background jobs should probably be explicitly defined in the request by more
      # than just the existence of a filename for the data.
      if run[:data_filename]
        begin
          pid = fork do
            # This will direct STDOUT in the child process to this file instead of its current setting.
            $stdout = File.new( Storage::User::File.data( run[:user_hash], run[:data_filename] ), 'w' )

            # Run the simulation in the child process.
            invoker.call
          end

          # We are not Zombies so reap the child process
          Process.detach( pid )
        rescue Exception => e
          log "Background job failed: #{e.message}"

          respond( response, 500, "Internal Server Error: #{e.message}" )
          return
        end

        # The background job has been successfully invoked so let the caller
        # know its all good.
        respond( response, 200, pid )

        log "Background Job PID: #{pid}"
      else
        log 'Running simulation...'

        # NOTE: What happens if the simulation fails for some reason?
        # Lets create a happy csv.
        response.start( 200 ) do |head, buffer|
          head[Mongrel::Const::CONTENT_TYPE] = 'application/save-as'
          head[Mongrel::Const::CONTENT_DISPOSITION] = "attachment; filename=#{run[:module_filename]}.csv"

          # STDOUT is used by the simulation framework to output results so we
          # override this to go the body of our document.
          $stdout = buffer

          invoker.call
        end

        log 'complete'
      end

      # We don't need the current lib path around in the server's path.
      log "Removed #{Storage::User::Dir.lib( run[:user_hash] )} from $LOAD_PATH"

      $LOAD_PATH.shift

      # Back to the server's stream
      $stdout = restore_stdout_to

      log '-- request end --'
    end
  end

  class << self
    # A pathetic little logger for the moment.
    def log( message )
      $stderr.puts( "** #{Time.now.strftime( '%Y-%m-%d %H:%I:%S' )}: #{message}" )
    end

    def load_settings
      settings = {
        :cwd => Dir.pwd,
        :port => 3000,
        :daemon => false,
        :address => 'localhost',
      }

      opts = GetoptLong.new(
        [ '-p', '--port', GetoptLong::OPTIONAL_ARGUMENT ],
        [ '-d', '--daemonize', GetoptLong::OPTIONAL_ARGUMENT ],
        [ '-P', '--pid', GetoptLong::OPTIONAL_ARGUMENT ],
        [ '-l', '--log', GetoptLong::OPTIONAL_ARGUMENT ],
        [ '-a', '--address', GetoptLong::OPTIONAL_ARGUMENT ],
        [ '-s', '--storage', GetoptLong::OPTIONAL_ARGUMENT ],
        [ '-C', '--config', GetoptLong::OPTIONAL_ARGUMENT ],
        [ '-f', '--force', GetoptLong::OPTIONAL_ARGUMENT ]
      )

      opts.each do |opt,arg|
        case opt
          when '-p', '--port'
            settings[:port] = arg
          when '-d', '--daemonize'
            settings[:daemon] = true
          when '-P', '--pid'
            settings[:pid_file] = "#{arg}.#{settings[:port]}"
          when '-l', '--log'
            settings[:log_file] = "#{arg}.#{settings[:port]}"
          when '-a', '--address'
            settings[:address] = arg
          when '-s', '--storage'
            settings[:storage] = arg
          when '-C', '--config'
            settings[:config] = arg
          when '-f', '--force'
            settings[:force] = true
        end
      end

      # Did we get a config file for the settings?  These will override the command line flags.
      if settings.has_key?( :config )
        settings[:config] += '/feynman_server_conf.yml' if File.directory?( settings[:config] )
  
        # YAML likes strings and we like symbols.
        YAML.load_file( settings[:config] ).each_pair { |k,v| settings[k.to_sym] = v }

        settings[:log_file] += ".#{settings[:port]}" unless settings[:log_file].match( /\.#{settings[:port]}/ )
        settings[:pid_file] += ".#{settings[:port]}" unless settings[:pid_file].match( /\.#{settings[:port]}/ )
      end

      # Override the default using the constant is a hash trick.
      Storage::DIR[:home] = settings[:storage] if settings.has_key?( :storage )

      # Provide suitable defaults for the log and pid files.
      settings[:log_file] = "log/feynman.log.#{settings[:port]}" unless settings.has_key?( :log_file )
      settings[:pid_file] = "log/feynman.pid.#{settings[:port]}" unless settings.has_key?( :pid_file )

      settings
    end

    def start( settings )
      stats = Mongrel::StatisticsFilter.new(:sample_rate => 1)

      config = Mongrel::Configurator.new( :host => settings[:address], :port => settings[:port], :pid_file => settings[:pid_file] ) do
        daemonize( :cwd => settings[:cwd], :log_file => settings[:log_file] ) if settings[:daemon]

          listener do
            uri "/simulation", :handler => SimulationHandler.new
            uri "/simulation", :handler => Mongrel::DeflateFilter.new
            uri "/simulation", :handler => stats
            uri "/authenticate", :handler => AuthenticateHandler.new
            uri "/authenticate", :handler => stats
            uri "/status", :handler => Mongrel::StatusHandler.new(:stats_filter => stats)
          end

          write_pid_file

          # This is used when not running as a daemon and allows the user to ctrl-c to stop
          # the server.
          trap( 'INT' ) do
            log 'Interrupt Received: Shutting down the feynman server...'

            stop

            File.delete( settings[:pid_file] )

            log 'complete'
          end
  
          run
      end

      log "Feynman Server running on #{settings[:address]}:#{settings[:port]}"

      config.join
    end

    # See bin/mongrel_rails from the mongrel gem for where I got the ideas in this method.
    def self.stop( settings )
      signal = ( settings[:force] ) ? 'KILL' : 'TERM'

      # Unlike the case of the start method where the appropriate log messages are written
      # within the context of the Mongrel::Configurator, we need to define the stderr stream
      # appropriately here.
      $stderr = File.new( settings[:log_file], 'a' ) if File.file?( settings[:log_file] )

      if File.file?( settings[:pid_file] )
        pid = open( settings[:pid_file] ).read.to_i
      else
        STDERR.puts "** Missing pid file: #{settings[:pid_file]}.  Feynman Server not running?"
        return
      end

      log "Sending #{signal} to FeynmanServer at PID: #{pid}" 

      begin
        Process.kill( signal, pid )
      rescue Errno::ESRCH
        log "Process does not exist.  Not running."
      end

      File.delete( settings[:pid_file] )

      log 'Done.  Server shutdown and not running.'
    end
  end
end

begin
  FeynmanServer.send( ARGV[0], FeynmanServer.load_settings )
rescue NoMethodError, TypeError => e
  STDERR.puts "Usage: ruby feynman_server.rb start|stop [options]"
end
