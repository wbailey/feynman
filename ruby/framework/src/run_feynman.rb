#!/usr/bin/env ruby
#
# == Synopsis
#
# This command line script is the responsible for setting up and running a
# simulation that has been developed using the Ruby version of the Feynman
# Simulation Framework.  See the documention in 
#
# == Usage
#
# ruby feynman.rb [OPTION] [MODULE_FILE]
#  -h|--help     This help message
#  -p|--profile  Turn on profiling which lists detailed execution statistics
#  -q|--quiet    Run the program without the ruby -w flag.
#
require 'feynman'
require 'getoptlong'
require 'rdoc/usage'

opts = GetoptLong.new(
  [ '--help', '-h', GetoptLong::NO_ARGUMENT ],
  [ '--profile', '-p', GetoptLong::NO_ARGUMENT ],
  [ '--quiet', '-q', GetoptLong::NO_ARGUMENT ]
)

$VERBOSE = true

opts.each do |opt, arg|
  case opt
    when '--profile'
      require 'profile'
    when '--help'
      RDoc::usage 'usage'
    when '--quiet'
      $VERBOSE = false
  end
end

RDoc::usage 'usage' unless ARGV.length.eql?( 1 )

# The name of the file containing the module which defines the simulation.
Feynman.Controller( ARGV[0] )
