#include "jungtable.h"
using namespace std;

//class Jungtable {
//public:
//    vector<vector<int>> body;
//
//    int push(int element){
//        //проверка на повторяемость элементов
//        int flag = 0;
//        for (int i = 0; i < body.size(); i++) {
//            for (int j = 0; j < body[i].size(); j++) {
//                if (element == body[i][j]) { flag++; }
//            }
//        }
//        if (flag != 0) { return 404; }
//
//        //добавление элемента
//        for (int i = 0; ; i++) {
//            if (body.size() < i + 1) {
//                body.push_back(vector<int>(1, element));
//                i = 0;
//                break;
//            }
//            else if (body[i][body[i].size() - 1] < element) {
//                body[i].push_back(element);
//                i = 0;
//                break;
//            }
//            else {
//                int position = body[i].size() - 1;
//                while (position >= 0 && element < body[i][position]) {
//                    position--;
//                }
//                int temp = body[i][position + 1];
//                body[i][position + 1] = element;
//                element = temp;
//            }
//        }
//        return 0;
//    }
//
//    int del(int x, int y) {
//        if (x > 0 && y > 0 && x <= body.size() && y == body[x].size()) {
//            x--;
//            y--;
//            int element = body[x][y];
//            body[x].erase(body[x].begin() + y);
//            for (int i = x - 1; i >= 0; i--) {
//                int position = body[i].size() - 1;
//                while (body[i][position] > element) {
//                    position--;
//                }
//                int temp = body[i][position];
//                body[i][position] = element;
//                element = temp;
//            }
//            return 0;
//        }
//        else { return 404; }
//    }
//
//    void print() {
//        for (int i = 0; i < body.size(); i++) {
//            for (int j = 0; j < body[i].size(); j++) {
//                cout << setw(3) << body[i][j];
//            }
//            cout << endl;
//        }
//    }
//};


int main()
{
    cout << "Hello World!\n";
    
    jungtable young;

    young.push(10);
    young.push(5);
    young.push(15);
    young.push(7);
    young.push(3);

    young.print();

    cout << young.del(3, 1) << endl;

    young.print();

}
