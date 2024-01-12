#include <bits/stdc++.h>
#include <iostream>

using namespace std;

// Kiểm tra ký tự có là chữ số hay không
int isDigit(char a){
	if('0' <= a && a <='9'){
		return 1;
		
	}
	return 0;
}

// Kiểm tra xâu có chứa chữ số hay không 
int check(string a){
	int n = a.length();
	for(int i = 0; i < n; i++){
		if(isDigit(a[i])){
			return 0;
		}
	}
	return 1;
}
// Mã hóa RLC với xâu không chứa chữ số
string rlc_encoding_without_number(const string& input){
	string out ="";
	if(check(input)){
		
    	int i = 0;
    	while(i < input.length()){
    		int count = 1;
    		while(i + 1 < input.length() && input[i] == input[i+1]){
    			count ++;
    			i++;
			}
			if(count >= 3){
				out += to_string(count) + input[i];
			}else{
				for(int q = 0; q < count ; q++){
					out += input[i];
				}
				 
			}
			i++;
		}
		return out;
	}
	return out;
	
}

// Giải mã xâu được mã hóa từ một xâu không chứa chữ số
string rlc_decoding_without_number(const string& input){
	string decoded_data = "";
    int i = 0;
    while (i < input.length()) {
        long count = 0;
        while (isdigit(input[i])) {
            count = count * 10 + (input[i] - '0');
            i++;
        }
        if (count > 0) {
            char current_char = input[i];
            for (int j = 0; j < count; j++) {
                decoded_data += current_char;
            }
        } else {
            decoded_data += input[i];
        }
        i++;
    }
    return decoded_data;
}

// Mã hóa RLC với xâu có chứa chữ số 
string rlc_encoding_with_number(const string& input){
	char dle = 0x10;
	string out ="";
	int i = 0;
	while(i < input.length()){
    		int count = 1;
    		while(i +1< input.length() && input[i] == input[i+1]){
    			count ++;
    			i++;
    			if(count == 9){
    				out +=	dle +  to_string(count) + input[i];
    				count = 0;		
				}
			}
			if(count >= 3){
				out += dle+ to_string(count) + input[i];
			}else{	
				for(int q = 0; q < count ; q++){
					out += input[i];
				}	
			}	
			i++;
		}
    return out;
}


//Giải mã xâu đã mã hóa từ một xâu có chứa chữ số 
string rlc_decoding_with_number(const string& input){
	char dle = 0x10;
	string out ="";
	int i = 0;
	while(i < input.length()){
		if(input[i] == dle){
			int count = input[i+1] - '0';
			
			for( int j = 0; j < count-1 ; j++){
				out += input[i+2];
			}
			i+=2;
		}
		out += input[i];
		i++;
	}
	return out;
}


// Trả về kích thước của file 
string formatFileSize(double size) {
    const char* units[] = {"Bytes", "KB", "MB", "GB", "TB"};
    int unitIndex = 0;
    while (size >= 1024 && unitIndex < 4) {
        size /= 1024;
        unitIndex++;
    }

    stringstream stream;
    stream << fixed << setprecision(2) << size << " " << units[unitIndex];
    return stream.str();
}


// Tiến hành mã hóa với file text không chứa chữ số.
// sử dụng hàm rlc_encoding_without_number trên từng dòng 
void rlc_encoding_file_without_number() {
	string inputFile;
	string ouputFile;

	cout <<"Nhập tên file bạn muốn nén: ";
	cin >> inputFile;
	cout << "Nhập tên file bạn muốn xuất: ";
	cin >> ouputFile;

	ifstream input(inputFile);
	ofstream output(ouputFile);
	if(input.is_open() && output.is_open()){

		// Bắt đầu đo thời gian
		auto start = std::chrono::high_resolution_clock::now();

		string line;
		int k ;
		while(getline(input,line)){
			if(check(line)){
				string outpuLine = rlc_encoding_without_number(line);
				output << outpuLine << endl;
			}else{
				cout<<"\nMã hóa bị dừng do văn bản có chứa chữ số." << endl;
				system("pause");
				return;
			}
			

			
		}
		// Kết thúc đo thời gian
		auto end = std::chrono::high_resolution_clock::now();

		// Tính thời gian đã trôi qua
		std::chrono::duration<double> elapsed = end - start;

		//cout <<"Mã hóa thành công." << endl;
		ifstream fileIn(inputFile,ios::binary);
		fileIn.seekg(0,ios::end);
		streampos fileInSize = fileIn.tellg();

		ifstream fileOu(ouputFile,ios::binary);
		fileOu.seekg(0,ios::end);
		streampos fileOuSize = fileOu.tellg();

		cout <<"\nKích thước file gốc: "<<formatFileSize(fileInSize) << endl;
		cout <<"Kích thước file nén: "<<formatFileSize(fileOuSize) << endl;
		
		double fileSizeIn = static_cast<double>(fileInSize);
		double fileSizeOut = static_cast<double>(fileOuSize);

		double HieuSuat = (fileSizeOut / fileSizeIn) * 100.0; 

		cout << "Hệ số nén file: " << HieuSuat << " %" << endl;
		cout <<"Thời gian thực thi: " <<elapsed.count() <<" giây.\n" << endl;
		
		input.close();
		output.close();
		

	}else{
		cout <<"\nThất bại do không thế mở file\n";
	}
	system("pause");
}

//Tiến hành giải mã với file text đã được mã hóa từ một file text không chứa chữ số 
// sử dụng hàm rlc_decoding_without_number trên từng dòng 
void rlc_decoding_file_without_number() {
	string inputFile;
	string ouputFile;

	cout <<"Nhập tên file bạn muốn giải mã: ";
	cin >> inputFile;
	cout << "Nhập tên file bạn muốn xuất: ";
	cin >> ouputFile;

	ifstream input(inputFile);
	ofstream output(ouputFile);
	if(input.is_open() && output.is_open()){

		// Bắt đầu đo thời gian
		auto start = std::chrono::high_resolution_clock::now();

		string line;
		while(getline(input,line)){
			
			string outpuLine = rlc_decoding_without_number(line);
			output << outpuLine << endl;
			
		}
		// Kết thúc đo thời gian
		auto end = std::chrono::high_resolution_clock::now();

		// Tính thời gian đã trôi qua
		std::chrono::duration<double> elapsed = end - start;

		cout <<"\nGiải mã  thành công." << endl;
		ifstream fileIn(inputFile,ios::binary);
		fileIn.seekg(0,ios::end);
		streampos fileInSize = fileIn.tellg();

		ifstream fileOu(ouputFile,ios::binary);
		fileOu.seekg(0,ios::end);
		streampos fileOuSize = fileOu.tellg();

		cout <<"\nKích thước file gốc: "<<formatFileSize(fileInSize) << endl;
		cout <<"Kích thước file giải mã: "<<formatFileSize(fileOuSize) << endl;
		
		double fileSizeIn = static_cast<double>(fileInSize);
		double fileSizeOut = static_cast<double>(fileOuSize);

		double HieuSuat = (fileSizeOut / fileSizeIn) * 100.0; 

		cout << "Tỉ lệ giải nén: " << HieuSuat << " %" << endl;
		cout <<"Thời gian thực thi: " <<elapsed.count() <<" giây.\n" << endl;
		
		input.close();
		output.close();
		

	}else{
		cout <<"\nThất bại do không thế mở file\n";
	}
	system("pause");
}

// Tiến hành mã hóa với file text có chứa chữ số 
// sử dụng hàm rlc_encoding_with_number trên từng dòng 
void rlc_encoding_file_with_number() {
	string inputFile;
	string ouputFile;

	cout <<"Nhập tên file bạn muốn nén: ";
	cin >> inputFile;
	cout << "Nhập tên file bạn muốn xuất: ";
	cin >> ouputFile;

	ifstream input(inputFile);
	ofstream output(ouputFile);
	if(input.is_open() && output.is_open()){

		// Bắt đầu đo thời gian
		auto start = std::chrono::high_resolution_clock::now();

		string line;
		while(getline(input,line)){
			
				string outpuLine = rlc_encoding_with_number(line);
				output << outpuLine << endl;
			
			
		}
		// Kết thúc đo thời gian
		auto end = std::chrono::high_resolution_clock::now();

		// Tính thời gian đã trôi qua
		std::chrono::duration<double> elapsed = end - start;

		cout <<"Mã hóa thành công." << endl;
		ifstream fileIn(inputFile,ios::binary);
		fileIn.seekg(0,ios::end);
		streampos fileInSize = fileIn.tellg();

		ifstream fileOu(ouputFile,ios::binary);
		fileOu.seekg(0,ios::end);
		streampos fileOuSize = fileOu.tellg();

		cout <<"\nKích thước file gốc: "<<formatFileSize(fileInSize) << endl;
		cout <<"Kích thước file nén: "<<formatFileSize(fileOuSize) << endl;
		
		double fileSizeIn = static_cast<double>(fileInSize);
		double fileSizeOut = static_cast<double>(fileOuSize);

		double HieuSuat = (fileSizeOut / fileSizeIn) * 100.0; 

		cout << "Hệ số nén file: " << HieuSuat << " %" << endl;
		cout <<"Thời gian thực thi: " <<elapsed.count() <<" giây.\n" << endl;
		

		input.close();
		output.close();

	}else{
		cout <<"\nThất bại do không thế mở file\n";
	}
	system("pause");
}

// Tiến hành giải mã với file text được mã hóa từ file text có chứa chữ số 
// sử dụng hàm rlc_decoding_with_number trên từng dòng 
void rlc_decoding_file_with_number() {
	string inputFile;
	string ouputFile;

	cout <<"Nhập tên file bạn muốn giải mã: ";
	cin >> inputFile;
	cout << "Nhập tên file bạn muốn xuất: ";
	cin >> ouputFile;

	ifstream input(inputFile);
	ofstream output(ouputFile);
	if(input.is_open() && output.is_open()){

		// Bắt đầu đo thời gian
		auto start = std::chrono::high_resolution_clock::now();

		string line;
		while(getline(input,line)){
			
			string outpuLine = rlc_decoding_with_number(line);
			output << outpuLine << endl;
			
		}
		// Kết thúc đo thời gian
		auto end = std::chrono::high_resolution_clock::now();

		// Tính thời gian đã trôi qua
		std::chrono::duration<double> elapsed = end - start;

		cout <<"\nGiải mã  thành công." << endl;
		ifstream fileIn(inputFile,ios::binary);
		fileIn.seekg(0,ios::end);
		streampos fileInSize = fileIn.tellg();

		ifstream fileOu(ouputFile,ios::binary);
		fileOu.seekg(0,ios::end);
		streampos fileOuSize = fileOu.tellg();

		cout <<"\nKích thước file gốc: "<<formatFileSize(fileInSize) << endl;
		cout <<"Kích thước file giải mã: "<<formatFileSize(fileOuSize) << endl;
		
		double fileSizeIn = static_cast<double>(fileInSize);
		double fileSizeOut = static_cast<double>(fileOuSize);

		double HieuSuat = (fileSizeOut / fileSizeIn) * 100.0; 

		cout << "Tỉ lệ giải nén: " << HieuSuat << " %" << endl;
		cout <<"Thời gian thực thi: " <<elapsed.count() <<" giây.\n" << endl;
		
		input.close();
		output.close();
		

	}else{
		cout <<"\nThất bại do không thế mở file\n";
	}
	system("pause");
}
int main(){
	char dle = 0x10;
	int choice;
	do{
		cout << endl <<"----Chương trình nén file văn bản bằng thuật toán RLC---" << endl;
		cout <<"1. Mã hóa file không chứa chữ số." << endl;
		cout <<"2. Giải mã file không chứa chữ số." << endl;
		cout <<"3. Mã hóa file có chứa chữ số" <<endl;
		cout <<"4. Giải mã file có chứa chữ số."<< endl;
		cout <<"5. Thoát chương trình" << endl;
		cout <<"Bạn chọn ?" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:{
			rlc_encoding_file_without_number();
			break;
		}
		case 2:{
			rlc_decoding_file_without_number();
			break;
		}
		case 3:{
			rlc_encoding_file_with_number();
			break;
		}
		case 4:{
			rlc_decoding_file_with_number();
			break;
		}
		case 5:{
			cout <<"Tạm biệt !" << endl;
			break;
		}

		default:
			cout <<"Lựa chọn không hợp lệ, vui lòng chọn lại !"<< endl;
			break;
		}
		
	}while(choice != 5);

	return 0;
}
