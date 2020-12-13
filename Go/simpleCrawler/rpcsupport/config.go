package rpcsupport

type config struct {
	RpcProtocol     string
	ElasticIndex    string
	ItemSaverRpc    string
	CrawlServiceRpc string
	ParseCity       string
	ParseCityList   string
	ParseProfile    string
	NilParser       string
	ItemSaverPort   string
}

var Config = config{
	RpcProtocol:     "tcp",
	ElasticIndex:    "dating_profile",
	ItemSaverRpc:    "ItemSaverService.Save",
	CrawlServiceRpc: "CrawlService.Process",
	ParseCity:       "ParseCity",
	ParseCityList:   "ParseCityList",
	ParseProfile:    "ParseProfile",
	NilParser:       "NilParser",
	ItemSaverPort:   ":1234"}
