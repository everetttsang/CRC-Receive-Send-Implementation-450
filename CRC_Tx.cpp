#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>
#include <bitset>
using namespace std;

string reverseString(string msg){
	int msgLen = msg.length();
  string output="";
	for (int i=0; i<msgLen; i++){
		output+=msg.at(msg.length()-1);
		msg = msg.substr(0,msg.length()-1);

		//cout << "Iteration: "<< i << " Output: "<< output<< " Msg now: "<< msg<< endl;
	}
	return output;
}

int bin2Dec (string str){
	int length = str.length();
	int i=0;
	int dec=0;
	//cout<< "Converting binary to decimal: "<<str<<endl;
	//cout << "length: "<< length<<endl;
	for (int i=0; i<str.length(); i++){
		//cout << str.at(i) <<endl;
		//cout<< str[i]<< endl;
		if (str[i]=='1'){

		  // cout<< "adding "<< pow(2,length-1-i)<<endl;
			dec += pow(2, length-1-i);

		}
	}




	return dec;
}

string dec2Bin (int dec){
	string binStr="";
	if (dec==0){
		binStr="0";
	}
  while (dec > 0){
		binStr += to_string(dec %2);

		dec /=2;

	}

  //cout << "Decimal to binary " << binStr<<endl;
	return reverseString(binStr);
}
void data() {
	// C %= modulo;
	return;
}

string appendZeros(string msg, string generator){
	//calculate # of 0's to append
	int zeroToAppend = generator.length()-1;
	for (int i=0; i< zeroToAppend; i++){
		msg+="0";
	}

	return msg;
}




  string calculateXOR(string &msg, string generator){
	string msgCpy = msg;
	string genCpy = generator;
	int len = generator.length();
  int a, b, c;
	int shiftCounter=0;
	string result;
	int found=0;
	string shiftMsg;
	// cout<< msgCpy<< endl;
	//cout << msgCpy.substr(0,generator.length())<< endl;
	a= bin2Dec(msgCpy.substr(0,generator.length()));
	b= bin2Dec(generator);
	c = a^b;
	// cout << "a: "<<a<<" b: "<<b<< " c: "<< c<< endl;
	result = dec2Bin(c);

	// cout << "result: "<< result<< endl<< " message: " << msg<<endl;
	shiftMsg= msg.substr(generator.length(),msg.length());
	if (c){
		msg = result +shiftMsg;
	}
	else {
		msg = shiftMsg;
	}

	// cout<< "Message: "<<msg<< endl;



	return result;
}

string generateCRC(string msg, string generator){
	string crc="0";
	msg = appendZeros(msg, generator);
  while (msg.length()>= generator.length() ){
		if(msg[0]=='1'){
			crc = calculateXOR(msg,generator);
			 // cout <<"1 found, processed: "<< msg <<endl;
		}
		else{

			msg=msg.substr(1,msg.length());
			// cout <<"0 found, processed: "<< msg <<endl;
		}
		// cout <<"Remainder: "<< crc <<endl;
		// cout <<"--------"<<endl;
	}
  if (bin2Dec(msg)==0)
		return "0";
	else
		return msg;
}



int main () {
  string line;
  ifstream myfile ("data2Tx.txt");
	//cout << "This is the zeros: "<<appendZeros("11111", "1010101010")<<endl;
  	// string message= "10011001";
   // calculateXOR(message,"11");
	 //cout<< message<<endl;
//	cout << "message: "<< message<< endl;
  // cout <<"Conversion 3: "<< bin2Dec("11")<< endl;
	// cout <<"Conversion 2: "<< bin2Dec("10")<< endl;
	// cout <<"Conversion 1: "<< bin2Dec("1")<< endl;
	// cout <<"Conversion 4: "<< bin2Dec("100")<< endl;
	// cout <<"Conversion 1: "<< bin2Dec("001")<< endl;
	// cout <<"Conversion 1: "<< bin2Dec("0000001")<< endl;
	// cout <<"Conversion 9: "<< bin2Dec("0001001")<< endl;
	//cout<< "This is the conversion"<<dec2Bin( 14)<< endl;
	//bin2Dec("1010100101001101001011010111110111000001011011001101100111000011");
//	cout << generateCRC("10001","111") <<endl;

  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
			string message;
			string generator;
			stringstream ss;
      ss << line;
			ss>> message >> generator;
			cout << "Message: "<<message << endl;
			cout << "Generator: "<<generator << endl;
			cout << "CRC: "<< generateCRC(message, generator) <<endl;
    }
    myfile.close();
  }

  else

  {
     cout << "Unable to open file";
     cout << "did this work 2?"<<endl;
  }
  return 0;
}
