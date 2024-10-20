
#ifndef TESTMapManager_H
#define TESTMAPMANAGER_H

class GameTexture;
#include <iostream>
#include <vector>
#include <string>
#include "types.h"

#include "GameTexture.h" 
#include "IMapManager.h"


class TestMapManager: public IMapManager {
public:
    //=============================================================================================
    //                              �R���X�g���N�^
    //=============================================================================================
    TestMapManager() : currentnumber(0), currentpartition(0),
        mapchip(0), mapdata({}),  backmap({}),
        primarymap({ false, {}, 0, 0 }),
        secondarymap({ false, {},0,0 })
     {}		                    

    //=============================================================================================
    //                              �f�X�g���N�^
    //=============================================================================================
    ~TestMapManager() = default;
   //=============================================================================================
   //                              ���C�t�T�C�N���֐�
   //=============================================================================================
    int Init() override;       //������
    int Update() override;     //�X�V
    int Draw() override;       //�`��

  //=============================================================================================
  //                              �}�b�v�`�b�v�摜�̃��[�h
  //=============================================================================================
    bool LoadMapChipTexture(std::shared_ptr<GameTexture> tex)override {
        // �e�N�X�`�����L�����ǂ������m�F����
        if (!tex) {
            std::cerr << "Failed to load map chip texture: tex is null." << std::endl;
            return false;  // ���s������
        }

        // ����ɓǂݍ��܂ꂽ�ꍇ
        mapchip = tex;
        return true;        // ����������
    }

  //=============================================================================================
  //                              Getter / Setter
  //=============================================================================================
    const std::vector<int>& GetDrawMapData() const override { return mapdata; } //�}�b�v�`�b�v��int�z���getter
    void SetDrawMapData(std::vector<int> copyvector) { mapdata = copyvector; }  //�}�b�v�`�b�v��int�z���setter


private:
    int currentnumber;			    //���݂̃X�e�[�W�ԍ����L������
    int currentpartition;			//�X�e�[�W�𕪊��������Ō��݂͉��Ԗڂ�������
    
    std::shared_ptr<GameTexture> mapchip;
    std::vector<int> backmap;
    std::vector<int> mapdata;
    
    MapStatus primarymap;
    MapStatus secondarymap;

    void MapDataUpdate(MapStatus& map,int startprogress);       //�`�ʂ���}�b�v�̔z����X�V����
};



#endif //TestMapManager_H