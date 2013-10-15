using System.Collections.Specialized;
using System.Net;
using System.Text;
using System.Windows.Forms;


namespace ProCon2013.Client
{
    public class ClientLib
    {
        private static readonly string PlayerIDFieldName = "playerid";
        private static readonly string AnswerFieldName = "answer";
        private static readonly string SubmitAnswerLocation = "/SubmitAnswer";

        public static string SubmitAnswer(string serverURL, string playerid, string ans)
        {
            byte[] res;
            using (var wc = new WebClient())
            {
				try {
					var nvc = new NameValueCollection();
					nvc.Add(PlayerIDFieldName, playerid);
					nvc.Add(AnswerFieldName, ans);
					res = wc.UploadValues("http://" + serverURL + SubmitAnswerLocation, nvc);
				}
				catch(WebException e) {
                    MessageBox.Show("通信に失敗しました。",
                       "エラー",
                       MessageBoxButtons.OK,
                       MessageBoxIcon.Error);
					return e.ToString();
				}

            }
            return Encoding.UTF8.GetString(res);
        }
    }
}