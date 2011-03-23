class CreateUsers < ActiveRecord::Migration
  def self.up
    create_table :user do |t|
      t.string :email_address, :limit => 60, :null => false
      t.string :password, :limit => 32, :null => false
      t.string :first_name, :limit => 30, :null => false
      t.string :last_name, :limit => 30, :null => false

      t.timestamps
    end
  end

  def self.down
    drop_table :users
  end
end
