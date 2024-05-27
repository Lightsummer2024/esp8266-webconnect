#ifndef A2024html.h
#define A2024html.h
const char* serwifihead = "<!DOCTYPE html>"
                           "<html lang=\"en\">"

                           "<head>"
                           " <meta charset=\"UTF-8\">"
                           "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"
                           "<title>设置您的WiFi网络</title>"
                           "</head>"

                           "<body>"
                           "<div  style=\"text-align: center;\" >"
                           "<h1>设置您的WiFi网络</h1>"
                           "<form>"
                           "<input style=\"background-color:transparent;border: 2px solid aqua;\" type=\"text\" name=\"ssid\" placeholder=\"ssid\">"
                           "<br>"
                           " <input style=\"background-color:transparent;border: 2px solid aqua;\" type=\"text\"   name=\"psk\" placeholder=\"psk\">"
                           " <br>"
                           "  <button type=\"submit\">保存设置</button>"
                           " </form>"

                           "<p>本网站访问者可设置您的WiFi网络!</p>"
                           "</div>"

                           "</body>"
                           "</html>";

const char* indexhtml = "<html><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><title>服务器状态</title><body><h1 style=\"color:red; text-align: center;\">当前服务器运行正常!</h1><p style=\"color:red; text-align: center;\">功能接口:/CDIR(查询文件目录)|/REFS(清除磁盘空间)|/CSD(查询内存使用量)|/IO?iopin=&ionum=(io控制)</p><input style=\"color:red; text-align: center;\" type=\"text\" id=\"czm\" placeholder=\"示例查询填写:CDIR\"><button style=\"color:red; text-align: center;\" onclick=\"var gett = new XMLHttpRequest; var czma = document.getElementById('czm').value; czma = '/' + czma; gett.open('GET', czma, true); gett.send();\">保存设置</button></body></html>";
const char* returnhtml = "<html><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><title>服务器状态</title><body><h1 style=\"color:red; text-align: center;\">操作运行成功!</h1><button onclick=\"var gett=new XMLHttpRequest; gett.open('GET','/',true);gett.send();\" style=\"color:red; text-align: center;\">返回</button></body></html>";

#endif