#include "path_trie.hpp"
#include "thread_pool.hpp"
#include <thread>

template <class HydraType>
class Hydra
{
   typedef std::function<bool (HydraType)> HydraHandler;
   typedef std::function<bool (std::atomic<bool> &exit,Hydra &parent)> HydraAgent;
   PathTrie<HydraHandler> mTrie;
   std::vector<std::thread> mAgents;
   std::atomic<bool> mExit;
   ThreadPool<HydraHandler,HydraType> mPool;

public:
	Hydra(int numThreads) : mPool(numThreads), mExit(false) {}

	~Hydra()
   {
      mExit = true;
      for (auto &agent : mAgents) {
         agent.join();
      }
   }

   void subscribe(const std::string &path, HydraHandler function)
   {
      mTrie.insert(path, function);
   }

   void enlist(HydraAgent agent)
   {
      mAgents.push_back(std::thread(agent,std::ref(mExit),std::ref(*this)));
   }

   void push_data(const std::string &path, HydraType input)
   {
      auto registered_functions = mTrie.match(path);
      for (auto &callback : registered_functions) {
         mPool.execute(callback,input);
      }
   }

};
