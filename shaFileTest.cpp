#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <fstream> 
#include <openssl/sha.h>
using namespace std;

unordered_map<string,vector<string>> filedetails; // sha -> chuncks sha
unordered_map<string,string> filenamedetails; //sha -> location


void getsha(char *res,int start,string path){

		FILE *f = fopen(path.c_str(),"rb");
	   char buffer[524288];
      memset(buffer,'\0',sizeof(buffer));
      fseek(f,start,SEEK_SET);
	   fread(buffer,1,524288,f);

		unsigned char SHA_Buffer[SHA_DIGEST_LENGTH];
		char buf[SHA_DIGEST_LENGTH*2];
		int i;
		memset(buf,'\0',sizeof(buf));
      memset(SHA_Buffer,'\0',sizeof(SHA_Buffer));
		SHA1((unsigned char *)buffer, 524288, SHA_Buffer);

		for (i=0; i < SHA_DIGEST_LENGTH; i++) {
			sprintf((char*)&(buf[i*2]), "%02x", SHA_Buffer[i]);
		}
		cout << "START:\n" << start << endl << ",filebytes:\n"<< buffer << endl << ",SHA_Buffer:\n"<<SHA_Buffer<< endl <<",buf hex:\n"<<buf<<endl<<endl<<endl;
      memset(res,'\0',sizeof(res));
		for(int i=0;i<SHA_DIGEST_LENGTH;i++){
				res[i]=buf[i];
			}
	fclose(f);
}

string addshatomap(string path){

	FILE* fp = fopen(path.c_str(),"rb");
	fseek(fp,0,SEEK_END);
	int size = ftell(fp);
	cout << path << " size: " << size << endl<<endl<<endl;
	fclose(fp);
	vector<string> v;
	string finalsha = "";
	int curr=0;
	while(size >0){
      char *res = new char[SHA_DIGEST_LENGTH*2];
      getsha(res,curr,path);
      string s="";
      for(int i=0;i<SHA_DIGEST_LENGTH;i++)
      {
            s= s+res[i];
      }
      v.push_back(s);
      finalsha = finalsha + s;
      curr= curr + 524288;
      size = size-524288;
  	}
  	filedetails[finalsha] = v;
  	filenamedetails[finalsha] = path;
  	return finalsha;
}


int main()
{
	addshatomap("/Users/piyush/Downloads/05BitTorrent.pdf");
	addshatomap("/Users/piyush/Downloads/dip_materials_slides.zip");
	cout<<"filenamedetails"<<endl;
	for (auto &p: filenamedetails) cout<<p.first<<':'<<p.second<<endl;
	cout<<"filedetails"<<endl;
	for (auto &p: filedetails){cout<<p.first<<':';for (auto &s: p.second)cout<<s<<','; cout<<endl;cout<<'('<<p.second.size()<<')'<<endl;}
	cout << "SHA_DIGEST_LENGTH:" << SHA_DIGEST_LENGTH << endl;
	return 0;
}