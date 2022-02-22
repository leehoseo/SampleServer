#include "ClientActor.h"
#include "ClientNetworkContents.h"
#include "ClientThreadContents.h"

ClientActor::ClientActor()
{
#define InsertContents(Contents) { Contents* contents = new Client##Contents(); insertContents(contents); };

	// NetworkContents
	InsertContents(NetworkContents);
	InsertContents(ThreadContents);
}

ClientActor::~ClientActor()
{
}
