#include "Artifact.h"

Artifact::Artifact(std::wstring _name, int _gold, std::wstring _desc, std::vector<std::pair<STATS, int>> _effects) :Item(_name, _gold, _desc, _effects) {
}
