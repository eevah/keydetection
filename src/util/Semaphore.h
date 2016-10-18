//#pragma once
//
//#include <string>
//
//namespace com
//{
//	namespace mixshare
//	{
//		namespace rapid_evolution
//		{
//			namespace util
//			{
//				namespace timing
//				{
//
//
//					using org::apache::log4j::Logger;
//
//					class Semaphore : public java::util::concurrent::Semaphore, public Serializable
//					{
//
//					private:
//						static const long long serialVersionUID = 0LL;
//						static Logger *log;
//
//						//////////////////
//						// CONSTRUCTORS //
//						//////////////////
//
//					public:
//						Semaphore(int i);
//
//						/////////////
//						// METHODS //
//						/////////////
//
//						virtual void release();
//
//						virtual void acquire(const std::string &description) throw(InterruptedException);
//
//						virtual void tryAcquire(const std::string &description, long long timeOutMillis) throw(InterruptedException);
//
//					};
//				}
//			}
//		}
//	}
//}
