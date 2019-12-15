#include "pch.h"
#include "Score.h"
#include "TopHighScore.h"

string Score::get_name()
{
	return this->name;
}

string Score::get_score()
{
	return this->score;
}

Score::Score(string Name, string Score)
{
	this->name = Name;
	this->score = Score;
}

Score::Score()
{
}

string Score::pushScore()
{
	//sf::Http::Request request("/getscore", sf::Http::Request::Post);
	std::ostringstream stream;
	stream << "?name=" << this->name << "&score=" << this->score;
	sf::Http::Request request("/score/pushscore"+stream.str(), sf::Http::Request::Get);

	// encode the parameters in the request body
	request.setBody(stream.str());
	//cout << request+"a";
	sf::Http http("http://www.thegioidochoila.com");
	sf::Http::Response response = http.sendRequest(request);

	// check the status
	if (response.getStatus() == sf::Http::Response::Ok)
	{
		// check the contents of the response
		return response.getBody();
		std::cout << response.getBody() << std::endl;
	}
	else
	{
		fstream f("highscore.txt", ios::out | ios::in);
		string bodyOfFile;
		getline(f, bodyOfFile);
		f.close();
		vector<Score*> listScore = TopHighScore().convertFromString(bodyOfFile);
		cout << bodyOfFile;
		vector<Score*> listNew;
		fstream f2("highscore.txt", ios::out);
		int count = 0;
		bool check = true;
		for (auto i:listScore)
		{
			
			cout << i->get_score() << " " << this->get_score()<<endl;
			if ((i->get_score()<this->get_score())||(i->get_score().length()<this->get_score().length()))
			{
				if ((check)&&(count < 5))
				{
					count++;
					check = false;
					//cout << this->get_name() << " " << this->get_score() << "," << endl;
					f2 << this->get_name() << " " << this->get_score() << ",";
					//listScore.pop_back();
				}
			}
			if (count<5)
			{
				count++;
				//cout << i->get_name() << " " << i->get_score() << ","<<endl;
				f2 << i->get_name() << " " << i->get_score() << ",";
			}
				
			
		}
		f2.close();
		return "fail";
	}
	
}
