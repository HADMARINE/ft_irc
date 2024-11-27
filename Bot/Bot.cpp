/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 12:47:22 by root              #+#    #+#             */
/*   Updated: 2024/11/27 15:52:48 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"

bool isServerShut = false;

static void signalHdlr(int sig) {
    (void)sig;
    isServerShut = true;
    std::cout << std::endl;
}

static std::string randomInsult() {
	std::string directory[ 77 ] = {
		"gomar",
		"Arschloch",
		"asshole",
		"ipurdia",
		"мудак",
		"seronjo",
		"задник",
		"idiota",
		"šupak",
		"røvhul",
		"Estúpido",
		"sitapea",
		"kusipää",
		"gilipollas"
		"asshole",
		"κώλος",
		"seggfej",
		"rassgat",
		"Stronzo",
		"dupsis",
		"asile",
		"шупак",
		"ħmar",
		"klootzak",
		"drittsekk",
		"dupek",
		"Idiotule",
		"засранец",
		"шупак",
		"kretén",
		"idiot",
		"kretén",
		"мудак",
		"רחמנות"
		"ապուշ",
		"göt",
		"သေနာကောင်",
		"混蛋",
		"බූරුවා",
		"항문",
		"სულელი",
		"ગધેડો",
		"गध",
		"下衆野郎",
		"ಕತ್ತೆ",
		"Нақұрыс",
		"ຮູກົ້ນ",
		"ആസ്ഹോൾ",
		"गाढव",
		"новш",
		"गधा",
		"گدی",
		"Tentak",
		"Аҳмақ",
		"கழுதை",
		"గాడిద",
		"ไอ้เวร",
		"Pislik",
		"thằng khốn nạn",
		"الأحمق",
		"מְטוּמטָם",
		"احمق",
		"gat",
		"Chitsiru",
		"dan iska",
		"Ike",
		"Sebono",
		"dabada",
		"punda",
		"Iwoomusu",
		"isiduli",
		"bajingan",
		"bangang",
		"Dondrom-belona",
		"pouaru",
		"bourik",
		"pugo",
		"podex",
	};
	return (directory[rand() % 77] + "\r\n");
}

Bot::Bot(std::string port, std::string pass) {
	int sock;
    struct sockaddr_in sin;
    std::string str;
	std::string parsingStr;
	char received[512] = "";
	size_t pos;
	signal(SIGINT, signalHdlr);
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        throw std::runtime_error("Erreur, socket non valide");
	}
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(atoi(port.c_str()));
    if (connect(sock, (struct sockaddr *)&sin, sizeof(sin)) == -1)
       throw std::runtime_error("Erreur de connexion.");
	str = "CAP LS\r\nPASS " + pass + "\r\nNICK veryAngryBot\r\nUSER veryAngryBot veryAngryBot localhost :veryAngryBot\r\n";
	send(sock, str.c_str(), str.size(), 0);
    while (isServerShut == false) {
		if (recv(sock, received, 512, 0) == -1)
			throw std::runtime_error("error while using recv");
		parsingStr = received;
		if (parsingStr.find("PRIVMSG") != std::string::npos) {
			pos = parsingStr.find("!");
			std::string sender = parsingStr.substr(1, pos - 1);
			pos = parsingStr.find(':', 1);
			std::string temp = parsingStr.substr(pos + 1, parsingStr.size());
			str = "PRIVMSG " + sender + " :" + randomInsult();
			send(sock, str.c_str(), str.size(), 0);
		}
		memset(&received, 0, sizeof(received));
	}
}

Bot::~Bot() {}

Bot::Bot(const Bot &cpy) {
	*this = cpy;
}

Bot &Bot::operator=(const Bot &cpy) {
	if (this == &cpy)
		return (*this);
	return (*this);
}
