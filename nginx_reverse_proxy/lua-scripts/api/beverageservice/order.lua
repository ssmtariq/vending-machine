local _M = {}

local function _StrIsEmpty(s)
	return s == nil or s == ''
end

function _M.Order()
	local OrderBeverageServiceClient = require "vending_machine_OrderBeverageService"
	local GenericObjectPool = require "GenericObjectPool"
	local ngx = ngx
	-- Read the parameters sent by the end user client
	
	ngx.req.read_body()
        local post = ngx.req.get_post_args()

        if (_StrIsEmpty(post.city_id) ) then
           ngx.status = ngx.HTTP_BAD_REQUEST
           ngx.say("Incomplete arguments")
           ngx.log(ngx.ERR, "Incomplete arguments")
           ngx.exit(ngx.HTTP_BAD_REQUEST)
        end

	ngx.say("Inside Nginx Lua script: Processing Order... Request from: ", post.city_id)
	
	local client = GenericObjectPool:connection(OrderBeverageServiceClient, "order-beverage-service", 9090)
	local status, ret = pcall(client.PlaceOrder, client, post.city_id)
--	client:PlaceOrder(1)
	GenericObjectPool:returnConnection(client)
	ngx.say("Status: ", status)

	if not status then
    
        	ngx.status = ngx.HTTP_INTERNAL_SERVER_ERROR
    		if (ret.message) then
      			ngx.header.content_type = "text/plain"
      			ngx.say("Failed to order: " .. ret.message)
      			ngx.log(ngx.ERR, "Failed to order: " .. ret.message)
    		else
      			ngx.header.content_type = "text/plain"
      			ngx.say("Failed to order: " )
      			ngx.log(ngx.ERR, "Failed to order: " )
    		end
    		ngx.exit(ngx.HTTP_OK)
  	else
    		ngx.header.content_type = "text/plain"
		ngx.say("Beverage Type: ", ret)
    		ngx.exit(ngx.HTTP_OK)
  	end

end

return _M
