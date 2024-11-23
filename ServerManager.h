#ifndef SERVERMANAGER_H
#define SERVERMANAGER_H
#define _TURN_OFF_PLATFORM_STRING  // 禁用cpprest的U宏
#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include <cpprest/uri.h>
#include <cpprest/uri_builder.h>
#include <cpprest/filestream.h>
#include <cpprest/containerstream.h>
#include <cpprest/producerconsumerstream.h>
#include <map>
#include <vector>
#include <string>
#include "db_config.h"
#include "poc.h"
#include <libssh/libssh.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include "Login.h"
#include "Command_Excute.h"
#include "Padding.h"
#include "scan/portScan.h"
#include "utils_scan.h"
#include "convert_string_t.h"
#include "poc_check.h"
#include <sys/stat.h>
#include"DatabaseHandler.h"
#include"utils.h"
#include"utils/config.h"
#include"mysql_connection_pool.h"


using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;
using namespace utility;
using namespace web::http::client;
using namespace concurrency::streams;
using namespace std;

class ServerManager {
public:
    ServerManager();
    void open_listener();
    void start();
    void stop();



private:

    // ´æ´¢portIdºÍservice_nameµÄmap
    std::map<std::string, std::string> port_services;

    std::unique_ptr<http_listener> listener;
    void handle_options(http_request request);
    void handle_request(http_request request);

    void handle_get_userinfo(http_request request);
    void handle_post_login(http_request request);
    void handle_get_cve_scan(http_request request);

    void handle_get_all_data(http_request request);
    void handle_search_data(http_request request);
    void handle_post_insert_data(http_request request);
    void handle_put_update_data_by_id(http_request request);
    void handle_delete_data_by_id(http_request request);
    void handle_post_get_Nmap(http_request request);
    void handle_post_hydra(http_request request);
    void handle_post_testWeak(http_request request);
    void handle_post_classify_protect(http_request request);
    void handle_get_classify_protect(http_request request);
    json::value Vuln_to_json(const Vuln& vuln);
    json::value ScanResult_to_json(const ScanResult& scan_result);
    json::value ScanHostResult_to_json(const ScanHostResult& scan_host_result);
    //将资产查询结果转成Json
    json::value convertToJson(const std::vector<IpVulnerabilities>& vulns);
    //POC列表转json（新增）
    json::value poc_list_to_json(const std::vector<POC>& poc_list);

    //检验文件是否存在，并获取文件名
    bool check_and_get_filename(const std::string& body, const std::string& content_type, std::string& filename, std::string& data, std::string& error_message);
    // 从内存中处理POC文件上传
    void upload_file(const std::string& filename, const std::string& data);
    // 将请求体保存到临时文件
    void save_request_to_temp_file(http_request request);
    //查看POC内容
    void handle_get_poc_content(http_request request);

    //POC搜索
    void handle_post_poc_search(http_request request);
    //POC验证
    void handle_post_poc_verify(http_request request);
    //设置需要执行POC验证的CVE条目
    void setIfCheckByIds(ScanHostResult& hostResult, const std::vector<std::string>& cve_ids, bool value);
    //执行并回显poc代码
    void handle_post_poc_excute(http_request request);
    //根据CVE编号添加POC代码、或更新已有的POC代码
    void update_poc_by_cve(http_request request);
    // 记录 /poc_callback 路径的请求（待修改）
    void log_poc_callback(const http_request& request);

    //插件化扫描
    void handle_post_poc_scan(http_request request);
    //合并两种漏洞扫描方法的结果
    void handle_merge_vuln_results(http_request request);
    //自动选择POC
    void handle_auto_select_poc(http_request request);
    
    //首页获取数据库中的资产数据，
    void handle_get_all_assets_vuln_data(http_request request);
    //scan_struct的相关结构体与数据库的交互
    
    ConnectionPool pool;
    DatabaseHandler dbHandler_;
    DatabaseManager dbManager;
    std::vector<POC> poc_list;
     
    // Additional member variables
    std::string global_ip;
    std::string global_pd;

    // Placeholder for SSH session and info
    // Define your own info_new and new_Event structures and initialize_ssh_session, fun, ConvertEvents, ServerInfo_Padding, convert functions accordingly.
    ServerInfo_t info_new;
    std::vector<event_t> new_Event;
    vector<event> Event;
    vector<scoreMeasure> vecScoreMeasure;

    //当前扫描结果
    vector<ScanHostResult> scan_host_result;
    //历史扫描结果
    HistoricalScanData historicalData;

};

#endif // SERVERMANAGER_H
