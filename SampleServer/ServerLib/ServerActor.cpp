#include "ServerActor.h"
#include "ServerNetworkContents.h"
#include "ServerThreadContents.h"

ServerActor::ServerActor()
{
#define InsertContents(Contents) { Contents* contents = new Server##Contents(); insertContents(contents); };

	InsertContents(NetworkContents);
	InsertContents(ThreadContents);
}

ServerActor::~ServerActor()
{

}