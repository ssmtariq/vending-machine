namespace cpp vending_machine
namespace py vending_machine
namespace lua vending_machine


enum ErrorCode {
  SE_CONNPOOL_TIMEOUT,
  SE_THRIFT_CONN_ERROR,
  SE_UNAUTHORIZED,
  SE_MEMCACHED_ERROR,
  SE_MONGODB_ERROR,
  SE_REDIS_ERROR,
  SE_THRIFT_HANDLER_ERROR,
  SE_RABBITMQ_CONN_ERROR
}

exception ServiceException {
    1: ErrorCode errorCode;
    2: string message;
}

struct location{
	1: i64 location_id;
	2: i64 city;
}

enum WeatherType{
	WARM,
	COLD
}

enum BeverageType{
	HOT,
	COLD
}



service OrderBeverageService{
	string PlaceOrder(
		1: i64 city
	)throws (1: ServiceException se)
}

service WeatherService{
	WeatherType GetWeather(
		1: i64 city
	)
}
service BeveragePreferenceService{
        string getBeverage(
                1: BeverageType btype
        )
}
