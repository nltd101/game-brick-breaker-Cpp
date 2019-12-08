#include "pch.h"
#include "TopHighScore.h"

bool checkTrash(char x) {
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

vector<Score*> covertFromString(string S) {
	
	vector<Score*> vt;
	string oject;
	for (int i = 0; i < S.length(); i++)
	{
		if (S[i] == ',')
		{
			cout << oject;
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
	sf::Http http("http://nltd101.work");
	sf::Http::Response response = http.sendRequest(request);
	if (response.getStatus() == sf::Http::Response::Ok)
	{
		return covertFromString(response.getBody());
	}
	else
	{
		vector<Score*> vt;
		vt.push_back(new Score("", "fail"));
		return vt;
	}
	
	
}

