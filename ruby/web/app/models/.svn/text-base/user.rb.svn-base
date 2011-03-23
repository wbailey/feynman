require 'digest/md5'

class User < ActiveRecord::Base
  class AuthenticationException < Exception
  end

  class << self
    def authenticate( email_address, password )
      result = find_by_sql( ['select * from user where email_address = ?', email_address.downcase ] )

      raise( AuthenticationException, "Record not found for #{email_address}" ) unless result.size > 0

      user = result[0]

      raise( AuthenticationException, "Record not found for #{email_address}" ) if user.nil?
      raise( AuthenticationException, "Password Mismatch" ) unless user.password.eql?( Digest::MD5.hexdigest( password ) )

      user
    end
  end
end
