#include "pch.h"
#include "Score.h"

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

string Score::pushScore()
{
	//sf::Http::Request request("/getscore", sf::Http::Request::Post);
	std::ostringstream stream;
	stream << "?name=" << this->name << "&score=" << this->score;
	sf::Http::Request request("/score/pushscore"+stream.str(), sf::Http::Request::Get);

	// encode the parameters in the request body
	request.setBody(stream.str());
	//cout << request+"a";
	sf::Http http("http://nltd101.work");
	sf::Http::Response response = http.sendRequest(request);

	// check the status
	if (response.getStatus() == sf::Http::Response::Ok)
	{
		// check the contents of the response
		std::cout << response.getBody() << std::endl;
	}
	else
	{
		std::cout << "request failed" << std::endl;
	}
	return string();
}
