#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <chrono>
#include <locale>
#include <thread>
#include <mutex>
#include "Queue.h"
#include <functional>
#include "FolderHelper.h"
#include "threads.h"

std::mutex mtx;
using namespace std;
int COUNT_THREAD = 4;

int main(int argc, char* argv[])
{

    if (argc != 3) {
        return 0;
    }
    else {
        if (strcmp(argv[1], "-t") || strcmp(argv[1], "--threads"))
            COUNT_THREAD = std::stoi(argv[2]);
        else
            return 0;
    }

    setlocale(LC_ALL, "Russian");
    //FolderHelper* fh = new FolderHelper();
    //fh->createFolder(fh->BASE_PATH, 6);
    //cout << fh->getDirectorySizeBytes("base");

    //for (int i = 0; i < 1; i++) {
    //    q->push(
    //        [](string s) {
    //            //std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    //            //return s + "__";
    //            FolderHelper* fh = new FolderHelper();
    //            unsigned long long size = fh->getDirectorySizeBytes(s);
    //            return to_string(size);
    //        }
    //    );
    //}


    queue* q = new queue();

    auto func_keyboard = [](queue* q) {
        FolderHelper* fh = new FolderHelper();
        // работа с клавой
        while (true) {
            string command = "";
            cin >> command;
            //cout << command << endl;
            if (command == "cancel") {
                q->clearQueue();
            }
            else if (command == "exit") {
                q->waitMode();      // помечаем что в режиме ожидания выполнения прошлых задач(не можем принимать новые запросы)
                q->isCanStop();     // ждем пока все запросы выполнятся
                q->stop();          // вырубаем все потоки, которые ждут очередную задачу
                return nullptr;     // завершаем поток работы с клавой(конец работы программы)
            }
            else if (fh->isPath(command)) {
                //cout << "это директория" << endl;

                q->push(
                    [command]() {
                        //std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                        //return s + "__";
                        FolderHelper* fh = new FolderHelper();
                        unsigned long long size = fh->getDirectorySizeBytes(command);
                        cout << command << ":" << size << endl;
                        return to_string(size);
                    }
                );
            }
            else {
                // Такого пути не существует, ничего не делаем
                cout << "error path" << endl;
            }

        }
    };

    // Логика работы потоков
    auto func = [](int threadNumber, int time, queue* q)
    {
        while (true) {
            // Изымаем из очереди задачу (ждем пока они появятся)
            std::function<std::string()> f = q->pop();
            if (f == nullptr) {
                // если получили нулл то пора завершать поток
                return nullptr;
            }
            f();
        }
    };

    vector<std::thread> threadPool = {};
    // поток работы с клавиатурой, тут считываем задачи, помещаем в очередь,
    //  из которой потом потоки будут брать таски
    threadPool.push_back(std::thread(func_keyboard, q));

    for (int i = 0; i < COUNT_THREAD; i++) {
        threadPool.push_back(std::thread(func, i, 1000, q));
    }

    for (std::thread& t : threadPool) {
        if (t.joinable()) {
            t.join();
        }
    }
}