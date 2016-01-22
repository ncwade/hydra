#include <boost/asio/io_service.hpp>
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>
#include <boost/range/irange.hpp>

template <class FunctionType, class FunctionInput>
class ThreadPool
{
	boost::asio::io_service mService;
	boost::thread_group mPool;
	boost::asio::io_service::work mWork;
public:

	ThreadPool(const int &numThreads) : mWork(mService)
	{
		for (auto i : boost::irange(0,numThreads))
		{
			mPool.create_thread(boost::bind(&boost::asio::io_service::run, &mService));
		}
	}

	~ThreadPool()
	{
		mService.stop();
		mPool.join_all();
	}

	// TODO: Update to use varidaic templates for multiple paramters
	void execute(FunctionType function, FunctionInput input)
	{
		mService.post(boost::bind(function, input));
	}

};
