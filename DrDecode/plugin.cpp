#include "plugin.h"
#include "hwbp.h"

//Initialize your plugin data here.
bool pluginInit(PLUG_INITSTRUCT* initStruct)
{
	_plugin_registercommand(pluginHandle, "DrDecode", [](int argc, char* argv[])
	{
		auto dr0 = DbgEval("dr0");
		auto dr1 = DbgEval("dr1");
		auto dr2 = DbgEval("dr2");
		auto dr3 = DbgEval("dr3");
		auto dr7 = DbgEval("dr7");
		auto dr6 = DbgEval("dr6");
		DR7 dr7s;
		uintdr7(dr7, &dr7s);
		auto printDrInfo = [&dr7s, dr6](unsigned int index, duint val)
		{
			auto mode2str = [](BYTE mode)
			{
				switch (HWBP_MODE(mode))
				{
				case HWBP_MODE::MODE_DISABLED: return "DISABLED";
				case HWBP_MODE::MODE_GLOBAL: return "  GLOBAL";
				case HWBP_MODE::MODE_LOCAL: return "   LOCAL";
				}
				return "???";
			};
			auto type2str = [](BYTE type)
			{
				switch (HWBP_TYPE(type))
				{
				case HWBP_TYPE::TYPE_EXECUTE: return "  EXECUTE";
				case HWBP_TYPE::TYPE_READWRITE: return "READWRITE";
				case HWBP_TYPE::TYPE_WRITE: return "    WRITE";
				}
				return "???";
			};
			auto size2str = [](BYTE size)
			{
				switch (HWBP_SIZE(size))
				{
				case HWBP_SIZE::SIZE_1: return "1";
				case HWBP_SIZE::SIZE_2: return "2";
				case HWBP_SIZE::SIZE_8: return "8";
				case HWBP_SIZE::SIZE_4: return "4";
				}
				return "???";
			};
			dprintf("Dr%u: 0x%p [Dr6: %d, Mode: %s, Type: %s, Size: %s]\n",
				index,
				val,
				(dr6 & (duint(1) << index)) != 0,
				mode2str(dr7s.HWBP_MODE[index]),
				type2str(dr7s.HWBP_TYPE[index]),
				size2str(dr7s.HWBP_SIZE[index])
			);
		};
		printDrInfo(0, dr0);
		printDrInfo(1, dr1);
		printDrInfo(2, dr2);
		printDrInfo(3, dr3);
		return true;
	}, true);
    return true; //Return false to cancel loading the plugin.
}

//Deinitialize your plugin data here.
void pluginStop()
{
}

//Do GUI/Menu related things here.
void pluginSetup()
{
}
