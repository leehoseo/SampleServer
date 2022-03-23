#include "ServerActor.h"
#include "ServerNetworkContents.h"
#include "ServerThreadContents.h"

ServerActor::ServerActor()
{
#define MAKE_CONTENTS(Contents) { Contents* contents = new Server##Contents(); insertContents(contents); };

	MAKE_CONTENTS(NetworkContents);
	MAKE_CONTENTS(ThreadContents);
}

ServerActor::~ServerActor()
{

}