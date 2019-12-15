#include "pch.h"
#include "TopHighScore.h"

bool TopHighScore:: checkTrash(char x) {
	if ((x=='[')||(x==']'))
	{
		return true;
	}
	if ((x == '{') || (x == '}'))
	{
		return true;
	}
	if ((x == ','))
	{
		return true;
	}
	return false;
}

vector<Score*> TopHighScore::convertFromString(string S) {
	
	vector<Score*> vt;
	string oject;
	for (int i = 0; i < S.length(); i++)
	{
		if (S[i] == ',')
		{
			//cout << oject;
			string word="";
			string name;
			for (int i = 0; i < oject.length(); i++)
			{
				if (oject[i] == ' ')
				{
					name = word;
					word = "";
				}
				else
				{
					word += oject[i];
				}

			}
			vt.push_back(new Score(name, word));
			oject = "";
		}
		else
		{
			if ((S[i] != '{') && (S[i] != '}'))
			{
				oject = oject + S[i];
			}

		}
	}
	return vt ;
}

vector<Score*> TopHighScore::getHighScore()
{
	sf::Http::Request request("/score/getscore", sf::Http::Request::Get);
	std::ostringstream stream;
	request.setBody(stream.str());
	sf::Http http("http://www.thegioidochoila.com");
	sf::Http::Response response = http.sendRequest(request);
	fstream f("highscore.txt", ios::out | ios::in);
	if (response.getStatus() == sf::Http::Response::Ok)
	{
		
	//	f << response.getBody();
		f.close();
		return convertFromString(response.getBody());
	}
	else
	{
		string bodyOfFile;
		getline(f, bodyOfFile);
		return convertFromString(bodyOfFile);
	}
}

