#define CURL_STATICLIB
#include<string>
#include<iostream>


#include<curl\curl.h>

/*
curl_easy_setopt - Устанавливает параметр для curl easy handle
ПАРАМЕТРЫ:
CURLOPT_WRITEFUNCTION - Эта функция вызывается в Libcurl, как только есть полученные данные, которые должны быть сохранены.
CURLOPT_WRITEDATA - записывает данные в поток FILE*, получая указатель из CURLOPT_WRITEFUNCTION
*/

static size_t write_data(char* ptr, size_t size, size_t nmemb, std::string* data)//функция для записи
/*

char * ptr — указатель на принимаемые данные(содержание страницы).
size_t(unsigned int) size — размер принимамого блока данных(size = 1)
size_t nmemb — общее количество блоков данных(количество байт).
string* data — это параметр опции CURLOPT_WRITEDATA, в который производится запись — наш буфер.

*/
{
    if (data)
    {
        data->append(ptr, size * nmemb);//метод класса string(добавляет к строке data данные из ptr)
        return size * nmemb; //Функция должна возвращать количество обработанных байт (size* nmemb)
    }
    else
        return 0;  // будет ошибка
}

int main()
{
    CURL* curl_handle;
    curl_handle = curl_easy_init();//инициализация

    if (curl_handle)
    {
        curl_easy_setopt(curl_handle, CURLOPT_URL, "http://api.openweathermap.org/data/2.5/weather?id=498817&appid=b14a922e9650b7e5050eb0a92ff20dcb");

        std::string content;//переменная, куда запишется результат
        curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &content);

        CURLcode res = curl_easy_perform(curl_handle);//Эта функция вызывается после инициализации и всех вызовов curl_easy_setopt 
        std::cout << content << std::endl;
        std::cerr << curl_easy_strerror(res) << std::endl;
        
        curl_easy_cleanup(curl_handle);//отчистка
    }

        return 0;   
    }
