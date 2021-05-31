#include <string>
#include <sstream>
#include <iostream>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <thread> 
using namespace std;



size_t WriteCallback(char* ptr, size_t size, size_t nmemb, void *f)
{
	FILE *file = (FILE *)f;

	return fwrite(ptr, size, nmemb, file);
}

void Download(string url, const char *filename)
{
	try
	{
		
		curlpp::Cleanup myCleanup;
		
		{		  


		  FILE *fp=stdout;

		  fp=fopen(filename,"wb");
		  curlpp::options::Url myUrl(url);
		  curlpp::Easy myRequest;
		  myRequest.setOpt(myUrl);
		  //curlpp::options::WriteFile ws(fp);
		  curlpp::options::WriteFunctionCurlFunction
			myFunction(WriteCallback);
		  curlpp::OptionTrait<void *, CURLOPT_WRITEDATA> 
			myData(fp);
		  //myRequest.setOpt(ws);
		  myRequest.setOpt(myFunction);
		  myRequest.setOpt(myData);
		  myRequest.setOpt(new curlpp::options::Verbose(true));
 		  myRequest.perform();
          
		  
	}
	}

	catch( curlpp::RuntimeError &e )
	{
		std::cout << e.what() << std::endl;
	}

	catch( curlpp::LogicError &e )
	{
		std::cout << e.what() << std::endl;
	}


}

int main(int, char **)
{

	string url1="https://drive.google.com/file/d/1NEPnErz253qYeByOj8lljKp665m8YwUI/view?usp=sharing";
	const char *filename1="img1.JPG";
	string url2="https://drive.google.com/file/d/1oglRqi7Zd4WhxtVMBiTZRSFqQtYG3IdG/view?usp=sharing";
	const char *filename2="img2.JPG";
	string url3="https://pern-my.sharepoint.com/:i:/g/personal/awais_cuiwah_edu_pk/EQ_C8OoSFb5EpMOA_taM2hQBrgdWvS1Tr5t_i_NFEfHsIA?e=K6XbOv";
	const char *filename3="img3.JPG";

	std::thread th1(Download,url1,filename1);
	std::thread th2(Download,url2,filename2);
	std::thread th3(Download,url3,filename3);

	th1.join();
	th2.join();
	th3.join();

  return 0;
}
