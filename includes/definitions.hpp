#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP

#include "ft_irc.hpp"

#define IRC_LISTEN_BACKLOG 100


// ~~~ DEBUG CMD DEF

#define DEBUG

#ifdef DEBUG

#define DCMD(x) x

#else

#define DCMD(x)

#endif

#endif

// ~~~ END ~~~