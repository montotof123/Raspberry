#include "GestionMCP6S28.h"

using namespace std;

GestionMCP6S28 mcp6s28(channel_1);

int main() {
	mcp6s28.setGain(mcp6s28.Gain_10);
	mcp6s28.setCanal(mcp6s28.In_0);
}