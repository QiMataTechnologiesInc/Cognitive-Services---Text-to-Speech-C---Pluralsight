#include <cpr/cpr.h>
#include <fstream>

int main() {
    //Retrieve Auth Token
    auto url = cpr::Url{ "https://eastus.api.cognitive.microsoft.com"
                         "/sts/v1.0/issuetoken" };
    auto header = cpr::Header{ {"Ocp-Apim-Subscription-Key", "{{ Your Subscription Key }}"} };
    auto body = cpr::Body {""};

    cpr::Session auth_session;
    auth_session.SetUrl(url);
    auth_session.SetHeader(header);
    auth_session.SetBody(body);
    auth_session.SetVerifySsl(false);

    auto auth_request = auth_session.Post();

    std::string bearer_token = auth_request.text;

    //Generate SSML
    auto ssml = "<speak version='1.0' xmlns=\"http://www.w3.org/2001/10/synthesis\" xml:lang='en-US'>\n"
                "<voice  name='Microsoft Server Speech Text to Speech Voice (en-US, Jessa24kRUS)'>\n"
                "    Welcome to Microsoft Cognitive Services <break time=\"100ms\" /> Text-to-Speech API.\n"
                "</voice> </speak>";

    //Create the request
    std::vector<cpr::Header> headers;
    headers.emplace_back(cpr::Header{ {"Content-Type", "application/ssml+xml"} });
    headers.emplace_back(cpr::Header{ {"X-Microsoft-OutputFormat", "audio-24khz-48kbitrate-mono-mp3"}});
    headers.emplace_back(cpr::Header{ {"User-Agent", "PluralsightDemo"}});
    headers.emplace_back(cpr::Header{ {"Authorization", " Bearer " + bearer_token } });

    cpr::Session audio_session;
    audio_session.SetUrl(cpr::Url{ "https://eastus.tts.speech.microsoft.com/cognitiveservices/v1" });
    audio_session.SetBody(cpr::Body {ssml});
    audio_session.SetHeaders(headers);
    audio_session.SetVerifySsl(false);

    auto text_to_speech_request = audio_session.Post();

    //Save the resulting file
    std::fstream out_file("speech.mpga",std::ios::out);
    out_file << text_to_speech_request.text;
    out_file.close();

    return 0;
}