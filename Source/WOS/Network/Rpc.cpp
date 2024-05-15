#include "Rpc.h"

TMap<uint16, std::pair<void*, std::function<void(std::span<char>)>>> RpcView::RpcFuncTable;
uint16 RpcView::RpcId = 0;