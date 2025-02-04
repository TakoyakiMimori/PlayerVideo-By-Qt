#pragma once
#include<windows.h>
#include<string>
typedef long long ssize_t;
#include<vlc/vlc.h>
#include<qwidget.h>
struct MediaSize {
    int length;
    int width;
    MediaSize(int _length, int _width)
    {
        length = _length;
        width =_width;
    }
};


class CVlc{
private:
    libvlc_instance_t* m_instance;
    libvlc_media_t* m_media;
    libvlc_media_player_t* m_player;
    HWND m_hwnd;
private:
    std::string ToUTF8(const std::wstring& str);
public:
    CVlc();
    ~CVlc();
    bool LoadMedia(const std::wstring& path);
    void SetHWnd(QWidget* widget);
    bool Play();
    bool Pause();
    bool Stop();
    float GetPosition();
    void SetPosition(float pos);
    int GetVolume();
    void SetVolume(int volume);
    float GetLength();
    bool SetRate(float rate);
    MediaSize GetMediaInfo();
};
