#ifndef THREAD_RUNNER_SIMPLE_HPP_INCLUDED
#define THREAD_RUNNER_SIMPLE_HPP_INCLUDED

#include "threadRunner.hpp"

class ThreadRunnerSimple : public ThreadRunner
{
public:
   virtual void run(boost::shared_ptr<MessageQueue> qeueu);
};


#endif
