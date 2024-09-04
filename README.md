# FT_IRC


## Règles
* Entourez par le namespace irc
```cpp
namespace irc {
    class Test {
    }
}
```
* Divisez bien les fichiers
* Nommez bien
    * ClassIsLikeThis
    * functionIsLikeThis
    * s_struct_is_like_this
    * t_type_is_like_this
    * namespace_is_like_this
    * variable_like_this or variableLikeThis


## TODO 
* Nickname verification https://modern.ircdocs.horse/#clients
* Parsing du config
* Réception des clients
* Lecture / Envoi
* Lise des commandes à implementer (cocher * après le nom de commande une fois implémenté)
    * PASS
    * KICK

## Liens utils
* How to open socket server in cpp : https://www.geeksforgeeks.org/socket-programming-in-cpp/
* Visual map of structure around user : https://www.linuxjournal.com/sites/default/files/inline-images/Erlang%20IRC%20Datamodel.png
* Standard doc : https://datatracker.ietf.org/doc/html/rfc1459

## How to use
* ./ircserv <password> <port>
    <password> : non void string value
    <port> : number in range of 1 ~ 65535 - port under 1024 is strictly not recommended since they're reserved
* ./ircserv help
    Show how to use
* Ctrl + c pour quitter

## Explications
### irc::Ircserv(t_irc_exec_conf &)
C'est le constructeur qui démarre du serveur. Utilisez toujours avec cette méthode. (non pas avec le défaut)
* _addrinfo : le structure qui contient toutes les données pour la création du serveur.
* _addrinfoHints : les contraintes pour créer le serveur, comme une ordonnance.
* _serverSock : fd du socket
* _password : mot de passe passé par le paramètre
* _isServeurShut : mettre `true` pour éteindre le serveur. Loop va arrêter la boucle.
