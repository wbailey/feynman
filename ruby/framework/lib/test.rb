require 'bigdecimal'

class BigDecimal
alias old_init initialize
def intialize( arg = nil )
  arg.nil? ? old_init( '0.0' ) : old_init( arg )
end
end

x = BigDecimal.new
