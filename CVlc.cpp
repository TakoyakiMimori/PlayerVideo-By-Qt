#include"header.h"
#include "CVlc.h"

std::string CVlc::ToUTF8(const std::wstring& str){
    int len = WideCharToMultiByte(CP_UTF8,0,str.data(),-1,0,0,0,0);
    std::string s;
    s.resize(len+1);
    WideCharToMultiByte(CP_UTF8,0,str.data(),-1,(LPSTR)s.data(),len+1,0,0);
    return s;



}

CVlc::CVlc() {
    m_instance = libvlc_new(0,NULL);
    m_media = NULL;
    m_player = NULL;
    m_hwnd = NULL;
}

CVlc::~CVlc() {
    if(m_player != NULL) {
        libvlc_media_player_release(m_player);
        m_player = NULL;
    }
    if(m_media != NULL) {
        libvlc_media_release(m_media);
        m_media = NULL;
    }
    if(m_instance != NULL) {
        libvlc_release(m_instance);
        m_instance = NULL;
    }
    if(m_hwnd != NULL) {
        m_hwnd = NULL;
    }
}

bool CVlc::LoadMedia(const std::wstring& path){
    if(m_instance == NULL) return false;
    std::string s = ToUTF8(path);
    if(m_media != NULL){
        libvlc_media_release(m_media);
        m_media = NULL;
    }
    m_media = libvlc_media_new_path(m_instance,s.data());
    if(m_media == NULL) return false;
    return true;
}

bool CVlc::SetHWnd(QWidget* widget){
    if(widget == nullptr){
        m_hwnd = NULL;
        return false;
    }
    m_hwnd = reinterpret_cast<HWND>(widget -> winId());
    if(m_player == NULL){
        m_player = libvlc_media_player_new_from_media(m_media);
        if(m_player == NULL) return false;
    }
    if(m_hwnd != NULL){
        libvlc_media_player_set_hwnd(m_player, m_hwnd);
    }
    return true;
}

bool CVlc::Play(){
    if(m_player == NULL) return false;
    int ret = libvlc_media_player_play(m_player);
    return ret == 0;
}

bool CVlc::Pause(){
    if(m_player == NULL) return false;
    libvlc_media_player_pause(m_player);
    return true;
}

bool CVlc::Stop(){
    if(m_player == NULL) return false;
    libvlc_media_player_stop(m_player);
    return true;
}

int CVlc::GetPosition(){
    if(m_player == NULL) return false;
    libvlc_time_t rm = libvlc_media_player_get_time(m_player);
    int pos = rm / 1000;
    return pos;
}

void CVlc::SetPosition(int pos){
    if(m_player == NULL) return;
    libvlc_media_player_set_time(m_player, (libvlc_time_t)(pos*1000));
}

int CVlc::GetVolume(){
    if(m_player == NULL) return false;
    float volume = libvlc_audio_get_volume(m_player);
    return volume;
}

void CVlc::SetVolume(int volume){
    if(m_player == NULL) return;
    libvlc_audio_set_volume(m_player, volume);
}

int CVlc::GetLength(){
    if(m_player == NULL) return -1;
    libvlc_time_t rm = libvlc_media_player_get_length(m_player);
    if(rm == -1) return -1;
    return rm/1000;
}

bool CVlc::SetRate(float rate){
    if(m_player == NULL) return false;
    return libvlc_media_player_set_rate(m_player, rate);
}

MediaSize CVlc::GetMediaInfo(){
    if(m_player == NULL) return MediaSize(0,0);
    unsigned width;
    unsigned height;
    libvlc_video_get_size(m_player,0,&width,&height);
    return MediaSize(
        (int)width,
        (int)height
        );
}

