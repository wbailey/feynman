class AuthController < ApplicationController
  skip_before_filter :verify_authenticity_token

  def standard
    @user = User.authenticate( params[:email_address], params[:password] )

    respond_to do |format|
      if @user
        format.html { redirect_to users_path( @user )  }
        format.xml { head :ok }
      else
        # not sure what to put here
      end
    end
  end
end
