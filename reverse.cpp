#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
using namespace std;
const size_t BUF_SIZE = 4096;

int reverse_file(string input_filename) {
    string output_filename = input_filename + ".rev";
    ifstream inFile(input_filename,ios::in|ios::binary); //二进制读方式打开
    ofstream outFile(output_filename, ios::out | ios::binary);

    streampos start_pos = inFile.tellg(); 
    inFile.seekg(0,   ios::end);  
    int64_t total_bytes = inFile.tellg(); 
    cout << "total_bytes:" << total_bytes << endl;
    //streampos end_pos = inFile.tellg(); 
    inFile.seekg(start_pos);  
    //exit(0);

    char buffer[BUF_SIZE];
    if(!inFile) {
        cout << "error" <<endl;
        return 0;
    }
    int read_bytes = 0;
    int64_t total_read_bytes = 0;
    int64_t read_blocks = 0;
    do {
        inFile.read(buffer, BUF_SIZE);  //一直读到文件结束
        read_bytes = inFile.gcount(); //看刚才读了多少字节
        if (!read_bytes) {
            break;
        }
        total_read_bytes += read_bytes;
        for (int i = 0; i < read_bytes; i++) {
            buffer[i] = ~buffer[i];
        }
        outFile.write(buffer, read_bytes);
        if (read_blocks % 2500 == 0) {
            //cout << "transform_bytes:" << total_read_bytes << "\n";
            cout << "                                 \r";
            cout << "transform_pct:" << static_cast<float>(total_read_bytes) / total_bytes * 100.0 << "%\r" << std::flush;;
            //cout << "transform_bytes:" << total_read_bytes << endl;
        }
        read_blocks +=1;
    } while (read_bytes == BUF_SIZE);
    
    inFile.close();
    outFile.close();
    return 0;
}

int main(int argc, char** argv) {
    assert(argc >= 1);
    cout << "argc" << argc << endl;
    for (int i = 1; i < argc; i++) {
        string filename(argv[i]);
        cout << filename << endl;
        reverse_file(string(filename));
    }
}