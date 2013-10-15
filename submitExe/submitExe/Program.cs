using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Windows.Forms;

namespace ProCon2013.Client
{
	class Program
	{
        // args str.txt パス
		static void Main(string[] args)
		{
			String serverUrl;
			String playerId; 
			String textUrl;

            // パス読み込み
			if(args.Length != 0){
				Properties.Settings.Default.TEXTURL = args[0];

			} 

            // Settings.settingsで読み込み
			serverUrl = Properties.Settings.Default.SERVER_URL;
			playerId = Properties.Settings.Default.PLAYER_ID;
			textUrl = Properties.Settings.Default.TEXTURL;
			

			try {
				StreamReader sr = new StreamReader(textUrl);
				String text = sr.ReadToEnd();
				Console.WriteLine( "server:"+serverUrl+" id:"+playerId+" text"+text );
				Console.WriteLine( "--> " + ClientLib.SubmitAnswer(serverUrl, playerId, text) );
				
				sr.Close();
			}
			catch(FileNotFoundException e) {
				Console.Write(e.Message);
                MessageBox.Show("ファイルがありません。",
                        "エラー",
                        MessageBoxButtons.OK,
                        MessageBoxIcon.Error);
			}
		}
	}
}
