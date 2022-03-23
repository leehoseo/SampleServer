#include "ClientActor.h"
#include "ClientNetworkContents.h"
#include "ClientThreadContents.h"

ClientActor::ClientActor()
{
#define MAKE_CONTENTS(Contents) { Contents* contents = new Client##Contents(); insertContents(contents); };

	// NetworkContents
	MAKE_CONTENTS(NetworkContents);
	MAKE_CONTENTS(ThreadContents);
}

ClientActor::~ClientActor()
{
}
