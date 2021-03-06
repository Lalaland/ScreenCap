#include "signalHandlerImpl.hpp"




std::unique_ptr<SignalHandler> SignalHandler::create(std::shared_ptr<MessageQueue> queue)
{
   return std::unique_ptr<SignalHandlerImpl>(new SignalHandlerImpl(queue));
}

SignalHandlerImpl::SignalHandlerImpl(std::shared_ptr<MessageQueue> queue) : SignalHandler(queue)
{
   sigemptyset(&set);
   sigaddset(&set,SIGINT);

   stoppedCapturer = false;
}


void SignalHandlerImpl::blockSignals()
{
   if (pthread_sigmask(SIG_BLOCK, &set, NULL) != 0)
   {
      perror("pthread_sigmask error");
      exit(1);
   }
}

void SignalHandlerImpl::setScreenCapturer(std::shared_ptr<ScreenCapturer> theCapturer)
{
   capturer = theCapturer;
}

void SignalHandlerImpl::handleSignal()
{
   int recievedSignal;
   int error = sigwait(&set,&recievedSignal);
   if (error != 0)
   {
      char buffer[40];
      strerror_r(error,buffer,sizeof(buffer));

      printf("it was invalid set %d %s\n",error,buffer);
      exit(1);
   }

   switch(recievedSignal)
   {
      case SIGINT:
         printf("I have been cntr-c ed\n");
         if (!stoppedCapturer)
         {
            capturer->pushIn(&ScreenCapturer::stopCapture);
            stoppedCapturer = true;
         }
         else
         {
            exit(1);
         }
         break;

      default:
         printf("Unknown signal\n");
         exit(1);
   };

   pushIn(&SignalHandler::handleSignal);
}

