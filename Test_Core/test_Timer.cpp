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

		// ステータスのテストに使用
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

		//BEGIN_TEST_METHOD_ATTRIBUTE(コンストラクタ初期値)
		//	TEST_PRIORITY(1)
		//END_TEST_METHOD_ATTRIBUTE()

		TEST_METHOD_INITIALIZE(TestInitialize){

		}

		TEST_METHOD_CLEANUP(TestCleanup){
			timer.reset();
		}

		TEST_METHOD(コンストラクタ初期値){
			writeMessage("In コンストラクタ初期値");

			pro::Timer timer;

			writeMessage("\tコンストラクタによる初期値");
			Assert::AreEqual(-1L,timer.getStartTime()
							,L"start_time != -1",LINE_INFO());
			Assert::AreEqual(-1L,timer.getStopTime()
							,L"stop_time != -1",LINE_INFO());
			Assert::AreEqual(0L,timer.getSumStop()
							,L"sum_stop != 0",LINE_INFO());

			writeMessage("\tコンストラクタ初期のステータス");
			Assert::AreEqual(static_cast<int>(pro::Timer::RESET)
							,static_cast<int>(timer.getState())
							,L"state != RESET",LINE_INFO());

			// ラップ用変数作成
			vector<clock_t> lap;
			const type_info& info = typeid(lap);

			writeMessage("\t型チェック");
			Assert::IsTrue(info==typeid(timer.getLapTime())
							,L"型がvector<clock_t>でありません",LINE_INFO());

			writeMessage("\tラップ初期化の確認");
			lap = timer.getLapTime();
			Assert::IsTrue(lap.empty()
							,L"lapが空でありません",LINE_INFO());
		
		}

		TEST_METHOD(ステータスの値を確認){
			writeMessage("In ステータスの値を確認");

			writeMessage("\t標準的な流れのテスト");
			timer.start();
			checkState(pro::Timer::START,L"RESET->start()");
			timer.stop();
			checkState(pro::Timer::STOP,L"START->stop()");
			timer.restart();
			checkState(pro::Timer::START,L"STOP->restart()");
			timer.reset();
			checkState(pro::Timer::RESET,L"START->reset()");

			writeMessage("\tRESET状態からの遷移");
			timer.stop();
			checkState(pro::Timer::RESET,L"RESET->stop()");
			timer.restart();
			checkState(pro::Timer::RESET,L"RESET->restart()");
			timer.reset();
			checkState(pro::Timer::RESET,L"RESET->reset()");
			timer.start();
			checkState(pro::Timer::START,L"RESET->start()");

			writeMessage("\tSTART状態からの遷移");
			timer.start();
			checkState(pro::Timer::START,L"START->start()");
			timer.restart();
			checkState(pro::Timer::START,L"START->restart()");
			timer.reset();
			checkState(pro::Timer::RESET,L"START->reset()");

			writeMessage("\tSTOP状態からの遷移");
			timer.start();
			timer.stop();
			timer.reset();
			checkState(pro::Timer::RESET,L"STOP->reset()");
			timer.start();
			timer.stop();
			timer.start();
			checkState(pro::Timer::START,L"STOP->start()");

		}

		TEST_METHOD(m_secメソッドテスト){
			writeMessage("In m_secメソッドテスト");
			
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
							,L"pro::Timer::PER_SECと一致しない",LINE_INFO());
			
			writeMessage(clock_per_sec_str);
			Assert::AreEqual(static_cast<long>(CLOCKS_PER_SEC),pro::Timer::m_sec(1)
							,L"CLOCKS_PER_SECと一致しない",LINE_INFO());
		}

		TEST_METHOD(startメソッドテスト){
			writeMessage("In startメソッドテスト");
			
			long start_time;

			writeMessage("\tstateの確認は ステータスの値を確認() を実行すること");


			writeMessage("\t標準的な流れのstart_timeの値確認");
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


			writeMessage("\t2回目のstart()と1回目のstart()の比較");
			timer.start();
			Assert::IsTrue(start_time < timer.getStartTime()
							,L"2回目のstart()と一回目のstart()の比較",LINE_INFO());

		}

		TEST_METHOD(stopメソッドテスト){
			writeMessage("In stopメソッドテスト");



		}
		TEST_METHOD(restartメソッドテスト){
			writeMessage("In restartメソッドテスト");

		}
		TEST_METHOD(resetメソッドテスト){
			writeMessage("In resetメソッドテスト");

			writeMessage("\tstateの確認は ステータスの値を確認() を実行すること");

			long stop_time;

			
			writeMessage("\t値変化の確認(start,sum_stop,lap)");
			timer.start();
			stop_time = timer.stop();
			while(stop_time == clock());
			timer.restart();
			timer.lap();
			Assert::AreNotEqual(-1L,timer.getStartTime()
							,L"start_time変化",LINE_INFO());
			Assert::AreNotEqual(0L,timer.getSumStop()
							,L"sum_stop変化",LINE_INFO());
			Assert::IsFalse(timer.getLapTime().empty()
							,L"lap変化",LINE_INFO());

			
			writeMessage("\trestによる初期化確認");
			timer.reset();
			Assert::AreEqual(-1L,timer.getStartTime()
							,L"start_time初期化",LINE_INFO());
			Assert::AreEqual(0L,timer.getSumStop()
							,L"sum_stop初期化",LINE_INFO());
			Assert::IsTrue(timer.getLapTime().empty()
							,L"lap初期化",LINE_INFO());

			
			writeMessage("\t値変化の確認(stop)");
			timer.start();
			timer.stop();
			Assert::AreNotEqual(-1L,timer.getStopTime()
							,L"stop_time変化",LINE_INFO());
			
			
			writeMessage("\trestによる初期化確認");
			timer.reset();
			Assert::AreEqual(-1L,timer.getStopTime()
							,L"stop_time初期化",LINE_INFO());


		}
		TEST_METHOD(lapメソッドテスト){
			writeMessage("In lapメソッドテスト");

		}
		TEST_METHOD(getDiffメソッドテスト){
			writeMessage("In getDiffメソッドテスト");

		}
		TEST_METHOD(getNowメソッドテスト){
			writeMessage("In getNowメソッドテスト");

		}


		//	TEST_METHOD(TimerNomal)
		//{
		//	Logger::WriteMessage("In TimerNomal");
		//	pro::Timer timer;
		//	//コンストラクタによる初期化
		//	Assert::AreEqual(-1,static_cast<int>(timer.getStartTime()),L"失敗getState()");
		//	Assert::AreEqual(-1,static_cast<int>(timer.getStopTime()),L"失敗getState()");
		//	Assert::AreEqual(0,static_cast<int>(timer.getSumStop()),L"失敗getState()");

		//	Assert::AreEqual(static_cast<int>( timer.m_sec(2) ),2000,L"m_sec");

		//	timer.setState(pro::Timer::RESET);
		//	Assert::AreEqual(static_cast<int>(pro::Timer::RESET),static_cast<int>(timer.getState()),L"失敗getState()");
		//	timer.start();
		//	Assert::AreEqual(static_cast<int>(pro::Timer::START),static_cast<int>(timer.getState()),L"失敗start ==");
		//	timer.stop();
		//	Assert::AreEqual(static_cast<int>(pro::Timer::STOP),static_cast<int>(timer.getState()),L"失敗stop ==");
		//	timer.restart();
		//	Assert::AreEqual(static_cast<int>(pro::Timer::START),static_cast<int>(timer.getState()),L"失敗restart ==");
		//	timer.reset();
		//	Assert::AreEqual(static_cast<int>(pro::Timer::RESET),static_cast<int>(timer.getState()),L"失敗reset"); 

		//	/*restart テストどうしよう
		//	 lap getDiff lap_time.back()これ何
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
		//	//ボケ処理
		//	timer.reset();
		//	Assert::AreEqual(static_cast<int>(timer.stop()),static_cast<int>(-1),L"失敗stop -1");
		//	Assert::AreEqual(static_cast<int>(timer.restart()),static_cast<int>(-1),L"失敗restart -1");
		//	Assert::AreEqual(static_cast<int>(timer.lap()),static_cast<int>(-1),L"失敗lap() -1");
		//	Assert::AreEqual(static_cast<int>(timer.getDiff()),static_cast<int>(-1),L"失敗 getDiff() -1");
		//	Assert::AreEqual(static_cast<int>(timer.getNow()),static_cast<int>(-1),L"失敗 getNow() -1"); 
		//}	
		//TEST_METHOD(Timervalue)
		//{
		//	pro::Timer timer;
		//	timer.reset();
		//	timer.start();
		//	Assert::IsTrue(static_cast<int>(timer.stop())<=static_cast<int>(timer.getNow())+5 && static_cast<int>(timer.stop())>=static_cast<int>(timer.getNow()),L"失敗 getNow() -1");
		//	timer.reset();
		//	timer.start();
		//	int sum=clock();
		//	timer.stop();
		//	Assert::IsTrue(static_cast<int>(timer.restart())<=static_cast<int>(clock()-timer.getStopTime())-sum+5 && static_cast<int>(timer.restart())>=static_cast<int>(clock()-timer.getStopTime())-sum,L"失敗 getNow() -1");
		//	Assert::IsTrue(static_cast<int>(timer.getNow())<=static_cast<int>(clock() -timer. getStopTime() - timer.getStartTime())+5 && static_cast<int>(timer.getNow())>=static_cast<int>(clock() -timer. getStopTime() - timer.getStartTime()),L"失敗 getNow() -1");
		//	timer.stop();
		//	Assert::IsTrue(static_cast<int>(timer.getNow())<=static_cast<int>(timer. getStopTime() - timer.getSumStop() - timer.getStartTime())+5 && static_cast<int>(timer.getNow())>=static_cast<int>(timer. getStopTime() - timer.getSumStop() - timer.getStartTime()),L"失敗 getNow() -1");
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
		//	//				,L"失敗 getNow()1 -1",LINE_INFO());
		//	timer.reset();
		//	timer.start();
		//	int sum=clock();
		//	timer.stop();
		//	Assert::IsTrue(static_cast<int>(timer.restart())<=static_cast<int>(clock()-timer.getStopTime())-sum+5 
		//				&& static_cast<int>(timer.restart())>=static_cast<int>(clock()-timer.getStopTime())-sum,L"失敗 getNow()2 -1",LINE_INFO());
		//	Assert::IsTrue(static_cast<int>(timer.getNow())<=static_cast<int>(clock() -timer. getSumStop() - timer.getStartTime())+5 
		//				&& static_cast<int>(timer.getNow())>=static_cast<int>(clock() -timer. getSumStop() - timer.getStartTime()),L"失敗 getNow()3 -1",LINE_INFO());
		//	timer.stop();
		//	Assert::IsTrue(static_cast<int>(timer.getNow())<=static_cast<int>(timer. getStopTime() - timer.getSumStop() - timer.getStartTime())+5 
		//				&& static_cast<int>(timer.getNow())>=static_cast<int>(timer. getStopTime() - timer.getSumStop() - timer.getStartTime()),L"失敗 getNow()4 -1",LINE_INFO());
		//}



	};
}