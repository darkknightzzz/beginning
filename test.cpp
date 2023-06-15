/***
//示例程序说明：调用币安API，获取LTCBTC交易对的近期成交信息，解析JSON，保存到本地文件
//create by yuhf <litter_boss@163.com>
***/

#include <fstream>
#include <iostream>
#include <string>
#include <memory>

// #include "curl/curl.h"
#include "rapidjson/document.h"

using namespace std;

class TradeData_T //存放交易信息
{
public:
    TradeData_T()
    {
        outFile.open("binance_trades_data.csv", ios::out);
        outFile << "symbol,id,price,qty,quoteQty,time,isBuyerMaker,isBestMatch" << std::endl;
    };
    ~TradeData_T()
    {
        outFile.close();
    };
    void printData(void)
    {
        std::cout << symbol << "," << id << "," << price << "," << qty << "," << quoteQty << "," << time << "," << (isBuyerMaker ? "TRUE" : "FALSE") << "," << (isBestMatch ? "TRUE" : "FALSE") << std::endl;
    }
    void writeCsvFile(void)
    {
        outFile << symbol << "," << id << "," << price << "," << qty << "," << quoteQty << "," << time << "," << (isBuyerMaker ? "TRUE" : "FALSE") << "," << (isBestMatch ? "TRUE" : "FALSE") << std::endl;
    }
    void setSymbol(const std::string str)
    {
        symbol = str;
    }

private:
    std::ofstream outFile;
    std::string symbol;

public:
    int id = 0;
    std::string price;
    std::string qty;
    std::string quoteQty;
    long long int time = 0;
    bool isBuyerMaker = false;
    bool isBestMatch = false;
};

// size_t req_reply(void *ptr, size_t size, size_t nmemb, void *stream)
// {
//     std::string *str = (std::string *)stream;
//     (*str).append((char *)ptr, size * nmemb);
//     return size * nmemb;
// }

// CURLcode getResponesStrByUrl(const std::string &url, std::string &response)
// {
//     CURLcode res = CURLE_OK;
//     CURL *curl = curl_easy_init();
//     if (curl)
//     {
//         struct curl_slist *header_list = NULL;
//         header_list = curl_slist_append(header_list, "User-Agent: Mozilla/5.0 (Windows NT 10.0; WOW64; Trident/7.0; rv:11.0) like Gecko");

//         curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header_list);
//         curl_easy_setopt(curl, CURLOPT_HEADER, 0);
//         curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
//         curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
//         curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, req_reply);
//         curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&response);
//         curl_easy_setopt(curl, CURLOPT_VERBOSE, 0); // debug

//         //设置代理，4780是本机0dcloud的http代理端口
//         curl_easy_setopt(curl, CURLOPT_PROXY, "127.0.0.1:4780");
//         curl_easy_setopt(curl, CURLOPT_PROXYTYPE, CURLPROXY_HTTP);
//         curl_easy_setopt(curl, CURLOPT_PROXYTYPE, 1L);
//         curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, FALSE);
//         curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, FALSE);

//         res = curl_easy_perform(curl);
//         curl_slist_free_all(header_list);
//     }
//     curl_easy_cleanup(curl);
//     return res;
// }

//响应报文示例
/*
[{"id":90494722,"price":"0.00312700","qty":"4.70800000","quoteQty":"0.01472191","time":1682214162161,"isBuyerMaker":false,"isBestMatch":true},
  {"id":90494723,"price":"0.00312700","qty":"12.36600000","quoteQty":"0.03866848","time":1682214162161,"isBuyerMaker":false,"isBestMatch":true}
]
*/

int convertJsonToClass(std::string &response, std::shared_ptr<TradeData_T> ptradeDate)
{
    if (response == "")
        return 0;

    rapidjson::Document doc;
    if (!doc.Parse<0>(response.c_str()).HasParseError())
    {
        assert(doc.IsArray());
        for (size_t i = 0; i < doc.Size(); i++)
        {
            assert(doc[i].IsObject());
            if (doc[i].HasMember("id") && doc[i]["id"].IsInt())
            {
                ptradeDate->id = doc[i]["id"].GetInt();
            }
            if (doc[i].HasMember("price") && doc[i]["price"].IsString())
            {
                ptradeDate->price = doc[i]["price"].GetString();
            }
            if (doc[i].HasMember("qty") && doc[i]["qty"].IsString())
            {
                ptradeDate->qty = doc[i]["qty"].GetString();
            }
            if (doc[i].HasMember("quoteQty") && doc[i]["quoteQty"].IsString())
            {
                ptradeDate->quoteQty = doc[i]["quoteQty"].GetString();
            }
            if (doc[i].HasMember("time") && doc[i]["time"].IsInt64())
            {
                ptradeDate->time = doc[i]["time"].GetInt64();
            }
            if (doc[i].HasMember("isBuyerMaker") && doc[i]["isBuyerMaker"].IsBool())
            {
                ptradeDate->isBuyerMaker = doc[i]["isBuyerMaker"].GetBool();
            }
            if (doc[i].HasMember("isBestMatch") && doc[i]["isBestMatch"].IsBool())
            {
                ptradeDate->isBestMatch = doc[i]["isBestMatch"].GetBool();
            }
            //ptradeDate->printData();
            ptradeDate->writeCsvFile();
        }
    }
    else
    {
        std::cout << doc.GetParseError() << std::endl;
    }
    return 0;
}



int main(int argc, char **argv)
{
    const std::string symbolstr = "LTCBTC";
    const std::string limit = "100"; //默认500，最大1000
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
