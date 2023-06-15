// #include <fstream>
#include <iostream>
#include <string>
// #include <memory>

// #include "curl/curl.h"
// #include "rapidjson/document.h"

using namespace std;

int main(int argc, char **argv)
{
    string symbolstr = "LTCBTC";
    // const std::string limit = "100"; //默认500，最大1000
    std::cout << "hello" <<std::endl;
    // step 1:获取交易数据
    // std::string getUrlStr = "https://api.binance.com/api/v3/trades?symbol=" + symbolstr + "&limit=" + limit;
    // std::string ResponseStr = "";
    // auto res = getResponesStrByUrl(getUrlStr, ResponseStr);
    // if (res != CURLE_OK)
    // {
    //     const char *errmsg = curl_easy_strerror(res);
    //     std::cout << "get trades failed! rc=" << res << ", errmsg=" << errmsg << std::endl;
    //     return 0;
    // }
    // else
    // {
    //     std::cout << "get trades ok!" << std::endl;
    //     //std::cout << ResponseStr << std::endl;
    // }

    // // step 2：解析JSON到内存对象
    // std::shared_ptr<TradeData_T> myptr(new TradeData_T());
    // myptr->setSymbol(symbolstr);
    // convertJsonToClass(ResponseStr, myptr);
    return 0;
}