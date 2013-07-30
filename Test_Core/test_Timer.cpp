#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include"Procon2013\Core\Core.h"
#include<sstream>

namespace test
{		

	TEST_CLASS(Timer)
	{
	private:

		pro::Timer timer;

		// �X�e�[�^�X�̃e�X�g�Ɏg�p
		void checkState(const pro::Timer::t_state& expected,const wchar_t* message=NULL){
			Assert::AreEqual(static_cast<int>(expected)
							,static_cast<int>(timer.getState())
							,message,LINE_INFO());
		}

	public:

		TEST_CLASS_INITIALIZE(TimerInitialize){
			writeMessage("In Timer Initialize");
		}

		TEST_CLASS_CLEANUP(TimerCleanup){
			writeMessage("In Timer Cleanup");
		}

		//BEGIN_TEST_METHOD_ATTRIBUTE(�R���X�g���N�^�����l)
		//	TEST_PRIORITY(1)
		//END_TEST_METHOD_ATTRIBUTE()

		TEST_METHOD_INITIALIZE(TestInitialize){

		}

		TEST_METHOD_CLEANUP(TestCleanup){
			timer.reset();
		}

		TEST_METHOD(�R���X�g���N�^�����l){
			writeMessage("In �R���X�g���N�^�����l");

			pro::Timer timer;

			writeMessage("\t�R���X�g���N�^�ɂ�鏉���l");
			Assert::AreEqual(-1L,timer.getStartTime()
							,L"start_time != -1",LINE_INFO());
			Assert::AreEqual(-1L,timer.getStopTime()
							,L"stop_time != -1",LINE_INFO());
			Assert::AreEqual(0L,timer.getSumStop()
							,L"sum_stop != 0",LINE_INFO());

			writeMessage("\t�R���X�g���N�^�����̃X�e�[�^�X");
			Assert::AreEqual(static_cast<int>(pro::Timer::RESET)
							,static_cast<int>(timer.getState())
							,L"state != RESET",LINE_INFO());

			// ���b�v�p�ϐ��쐬
			vector<clock_t> lap;
			const type_info& info = typeid(lap);

			writeMessage("\t�^�`�F�b�N");
			Assert::IsTrue(info==typeid(timer.getLapTime())
							,L"�^��vector<clock_t>�ł���܂���",LINE_INFO());

			writeMessage("\t���b�v�������̊m�F");
			lap = timer.getLapTime();
			Assert::IsTrue(lap.empty()
							,L"lap����ł���܂���",LINE_INFO());
		
		}

		TEST_METHOD(�X�e�[�^�X�̒l���m�F){
			writeMessage("In �X�e�[�^�X�̒l���m�F");

			writeMessage("\t�W���I�ȗ���̃e�X�g");
			timer.start();
			checkState(pro::Timer::START,L"RESET->start()");
			timer.stop();
			checkState(pro::Timer::STOP,L"START->stop()");
			timer.restart();
			checkState(pro::Timer::START,L"STOP->restart()");
			timer.reset();
			checkState(pro::Timer::RESET,L"START->reset()");

			writeMessage("\tRESET��Ԃ���̑J��");
			timer.stop();
			checkState(pro::Timer::RESET,L"RESET->stop()");
			timer.restart();
			checkState(pro::Timer::RESET,L"RESET->restart()");
			timer.reset();
			checkState(pro::Timer::RESET,L"RESET->reset()");
			timer.start();
			checkState(pro::Timer::START,L"RESET->start()");

			writeMessage("\tSTART��Ԃ���̑J��");
			timer.start();
			checkState(pro::Timer::START,L"START->start()");
			timer.restart();
			checkState(pro::Timer::START,L"START->restart()");
			timer.reset();
			checkState(pro::Timer::RESET,L"START->reset()");

			writeMessage("\tSTOP��Ԃ���̑J��");
			timer.start();
			timer.stop();
			timer.reset();
			checkState(pro::Timer::RESET,L"STOP->reset()");
			timer.start();
			timer.stop();
			timer.start();
			checkState(pro::Timer::START,L"STOP->start()");

		}

		TEST_METHOD(m_sec���\�b�h�e�X�g){
			writeMessage("In m_sec���\�b�h�e�X�g");
			
			string per_sec_str,clock_per_sec_str;

#ifdef TEST_MESSAGE
			std::stringstream ss;
			ss << "\tpro::Timer::PER_SEC = " << pro::Timer::PER_SEC;
			per_sec_str = ss.str();
			ss.str("");
			ss.clear(std::stringstream::goodbit);
			ss << "\tCLOCKS_PER_SEC = " << CLOCKS_PER_SEC;
			clock_per_sec_str = ss.str();
#endif

			writeMessage(per_sec_str);
			Assert::AreEqual(pro::Timer::PER_SEC,pro::Timer::m_sec(1)
							,L"pro::Timer::PER_SEC�ƈ�v���Ȃ�",LINE_INFO());
			
			writeMessage(clock_per_sec_str);
			Assert::AreEqual(static_cast<long>(CLOCKS_PER_SEC),pro::Timer::m_sec(1)
							,L"CLOCKS_PER_SEC�ƈ�v���Ȃ�",LINE_INFO());
		}

		TEST_METHOD(start���\�b�h�e�X�g){
			writeMessage("In start���\�b�h�e�X�g");
			
			long start_time;

			writeMessage("\tstate�̊m�F�� �X�e�[�^�X�̒l���m�F() �����s���邱��");


			writeMessage("\t�W���I�ȗ����start_time�̒l�m�F");
			Assert::AreEqual(-1L,timer.getStartTime()
							,L"reset()->start_time",LINE_INFO());
			timer.start();
			start_time = timer.getStartTime();
			Assert::AreNotEqual(-1L,timer.getStartTime()
							,L"start()->start_time",LINE_INFO());
			Assert::AreEqual(start_time,timer.getStartTime()
							,L"start()->start_time",LINE_INFO());
			timer.stop();
			Assert::AreNotEqual(-1L,timer.getStartTime()
							,L"stop()->start_time",LINE_INFO());
			Assert::AreEqual(start_time,timer.getStartTime()
							,L"stop()->start_time",LINE_INFO());
			timer.restart();
			Assert::AreNotEqual(-1L,timer.getStartTime()
							,L"restart()->start_time",LINE_INFO());
			Assert::AreEqual(start_time,timer.getStartTime()
							,L"restart()->start_time",LINE_INFO());
			timer.reset();
			Assert::AreEqual(-1L,timer.getStartTime()
							,L"reset()->start_time",LINE_INFO());


			writeMessage("\t2��ڂ�start()��1��ڂ�start()�̔�r");
			timer.start();
			Assert::IsTrue(start_time < timer.getStartTime()
							,L"2��ڂ�start()�ƈ��ڂ�start()�̔�r",LINE_INFO());

		}

		TEST_METHOD(stop���\�b�h�e�X�g){
			writeMessage("In stop���\�b�h�e�X�g");



		}
		TEST_METHOD(restart���\�b�h�e�X�g){
			writeMessage("In restart���\�b�h�e�X�g");

		}
		TEST_METHOD(reset���\�b�h�e�X�g){
			writeMessage("In reset���\�b�h�e�X�g");

			writeMessage("\tstate�̊m�F�� �X�e�[�^�X�̒l���m�F() �����s���邱��");

			long stop_time;

			
			writeMessage("\t�l�ω��̊m�F(start,sum_stop,lap)");
			timer.start();
			stop_time = timer.stop();
			while(stop_time == clock());
			timer.restart();
			timer.lap();
			Assert::AreNotEqual(-1L,timer.getStartTime()
							,L"start_time�ω�",LINE_INFO());
			Assert::AreNotEqual(0L,timer.getSumStop()
							,L"sum_stop�ω�",LINE_INFO());
			Assert::IsFalse(timer.getLapTime().empty()
							,L"lap�ω�",LINE_INFO());

			
			writeMessage("\trest�ɂ�鏉�����m�F");
			timer.reset();
			Assert::AreEqual(-1L,timer.getStartTime()
							,L"start_time������",LINE_INFO());
			Assert::AreEqual(0L,timer.getSumStop()
							,L"sum_stop������",LINE_INFO());
			Assert::IsTrue(timer.getLapTime().empty()
							,L"lap������",LINE_INFO());

			
			writeMessage("\t�l�ω��̊m�F(stop)");
			timer.start();
			timer.stop();
			Assert::AreNotEqual(-1L,timer.getStopTime()
							,L"stop_time�ω�",LINE_INFO());
			
			
			writeMessage("\trest�ɂ�鏉�����m�F");
			timer.reset();
			Assert::AreEqual(-1L,timer.getStopTime()
							,L"stop_time������",LINE_INFO());


		}
		TEST_METHOD(lap���\�b�h�e�X�g){
			writeMessage("In lap���\�b�h�e�X�g");

		}
		TEST_METHOD(getDiff���\�b�h�e�X�g){
			writeMessage("In getDiff���\�b�h�e�X�g");

		}
		TEST_METHOD(getNow���\�b�h�e�X�g){
			writeMessage("In getNow���\�b�h�e�X�g");

		}


		//	TEST_METHOD(TimerNomal)
		//{
		//	Logger::WriteMessage("In TimerNomal");
		//	pro::Timer timer;
		//	//�R���X�g���N�^�ɂ�鏉����
		//	Assert::AreEqual(-1,static_cast<int>(timer.getStartTime()),L"���sgetState()");
		//	Assert::AreEqual(-1,static_cast<int>(timer.getStopTime()),L"���sgetState()");
		//	Assert::AreEqual(0,static_cast<int>(timer.getSumStop()),L"���sgetState()");

		//	Assert::AreEqual(static_cast<int>( timer.m_sec(2) ),2000,L"m_sec");

		//	timer.setState(pro::Timer::RESET);
		//	Assert::AreEqual(static_cast<int>(pro::Timer::RESET),static_cast<int>(timer.getState()),L"���sgetState()");
		//	timer.start();
		//	Assert::AreEqual(static_cast<int>(pro::Timer::START),static_cast<int>(timer.getState()),L"���sstart ==");
		//	timer.stop();
		//	Assert::AreEqual(static_cast<int>(pro::Timer::STOP),static_cast<int>(timer.getState()),L"���sstop ==");
		//	timer.restart();
		//	Assert::AreEqual(static_cast<int>(pro::Timer::START),static_cast<int>(timer.getState()),L"���srestart ==");
		//	timer.reset();
		//	Assert::AreEqual(static_cast<int>(pro::Timer::RESET),static_cast<int>(timer.getState()),L"���sreset"); 

		//	/*restart �e�X�g�ǂ����悤
		//	 lap getDiff lap_time.back()���ꉽ
		//	Assert::AreEqual(3,3,
		//		// Tolerance:
		//		0.01,
		//		// Message:
		//		L"Basic test failed",
		//		// Line number - used if there is no PDB file:
		//		LINE_INFO());:*/			
	
		//}	
		//TEST_METHOD(TimerAbso)
		//{
		//	Logger::WriteMessage("In TimerAbso");
		//	pro::Timer timer;
		//	//�{�P����
		//	timer.reset();
		//	Assert::AreEqual(static_cast<int>(timer.stop()),static_cast<int>(-1),L"���sstop -1");
		//	Assert::AreEqual(static_cast<int>(timer.restart()),static_cast<int>(-1),L"���srestart -1");
		//	Assert::AreEqual(static_cast<int>(timer.lap()),static_cast<int>(-1),L"���slap() -1");
		//	Assert::AreEqual(static_cast<int>(timer.getDiff()),static_cast<int>(-1),L"���s getDiff() -1");
		//	Assert::AreEqual(static_cast<int>(timer.getNow()),static_cast<int>(-1),L"���s getNow() -1"); 
		//}	
		//TEST_METHOD(Timervalue)
		//{
		//	pro::Timer timer;
		//	timer.reset();
		//	timer.start();
		//	Assert::IsTrue(static_cast<int>(timer.stop())<=static_cast<int>(timer.getNow())+5 && static_cast<int>(timer.stop())>=static_cast<int>(timer.getNow()),L"���s getNow() -1");
		//	timer.reset();
		//	timer.start();
		//	int sum=clock();
		//	timer.stop();
		//	Assert::IsTrue(static_cast<int>(timer.restart())<=static_cast<int>(clock()-timer.getStopTime())-sum+5 && static_cast<int>(timer.restart())>=static_cast<int>(clock()-timer.getStopTime())-sum,L"���s getNow() -1");
		//	Assert::IsTrue(static_cast<int>(timer.getNow())<=static_cast<int>(clock() -timer. getStopTime() - timer.getStartTime())+5 && static_cast<int>(timer.getNow())>=static_cast<int>(clock() -timer. getStopTime() - timer.getStartTime()),L"���s getNow() -1");
		//	timer.stop();
		//	Assert::IsTrue(static_cast<int>(timer.getNow())<=static_cast<int>(timer. getStopTime() - timer.getSumStop() - timer.getStartTime())+5 && static_cast<int>(timer.getNow())>=static_cast<int>(timer. getStopTime() - timer.getSumStop() - timer.getStartTime()),L"���s getNow() -1");
		//}
		//TEST_METHOD(TimerVeror)
		//{
		//	Logger::WriteMessage("In TimerVeror");
		//	pro::Timer timer;
		//	try
		//	{
		//		timer.lap(-1);
		//		Assert::IsTrue(0<1);
		//	}
		//	catch(pro::OutOfRangeException<long> e){
		//		e.showError();
		//	}	
		//}

		//TEST_METHOD(TimerValue)
		//{
		//	Logger::WriteMessage("In TimerValue");
		//	pro::Timer timer;
		//	timer.reset();
		//	timer.start();
		//	//Assert::IsTrue(static_cast<int>(timer.stop())<=static_cast<int>(timer.getNow())+5
		//	//			&& static_cast<int>(timer.stop())>=static_cast<int>(timer.getNow())
		//	//				,L"���s getNow()1 -1",LINE_INFO());
		//	timer.reset();
		//	timer.start();
		//	int sum=clock();
		//	timer.stop();
		//	Assert::IsTrue(static_cast<int>(timer.restart())<=static_cast<int>(clock()-timer.getStopTime())-sum+5 
		//				&& static_cast<int>(timer.restart())>=static_cast<int>(clock()-timer.getStopTime())-sum,L"���s getNow()2 -1",LINE_INFO());
		//	Assert::IsTrue(static_cast<int>(timer.getNow())<=static_cast<int>(clock() -timer. getSumStop() - timer.getStartTime())+5 
		//				&& static_cast<int>(timer.getNow())>=static_cast<int>(clock() -timer. getSumStop() - timer.getStartTime()),L"���s getNow()3 -1",LINE_INFO());
		//	timer.stop();
		//	Assert::IsTrue(static_cast<int>(timer.getNow())<=static_cast<int>(timer. getStopTime() - timer.getSumStop() - timer.getStartTime())+5 
		//				&& static_cast<int>(timer.getNow())>=static_cast<int>(timer. getStopTime() - timer.getSumStop() - timer.getStartTime()),L"���s getNow()4 -1",LINE_INFO());
		//}



	};
}