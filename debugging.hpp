// Debug macros
// You need to define debug macro before including this file
#if DEBUG
	#define DEBUG_START(label) std::cout<<label<<" Start\n"<<std::flush;
	#define DEBUG_FINISH(label) std::cout<<label<<" Finish\n"<<std::flush;
	#define DEBUG_FLAG(label)  std::cout<<label<<"\n"<<std::flush;
#else
	#define DEBUG_START(label)
	#define DEBUG_FINISH(label)
	#define DEBUG_FLAG(label)
#endif
