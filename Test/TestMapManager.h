
#ifndef TESTMapManager_H
#define TESTMAPMANAGER_H

class GameTexture;
class ResourceManager;
class SpriteRenderer;

#include <iostream>
#include <vector>
#include "IMapManager.h"
#include "types.h"


class TestMapManager: public IMapManager {
public:
    // �R���X�g���N�^
    TestMapManager(std::shared_ptr<ResourceManager> rm);

   //=============================================================================================
   //                              ���C�t�T�C�N���֐�
   //=============================================================================================
    int Init() override;       //������
    int Update() override;     //�X�V
    int Draw() override;       //�`��

  //=============================================================================================
  //                              �}�b�v�`�b�v�摜�̃��[�h
  //=============================================================================================
    bool LoadMapChipTexture(std::shared_ptr<GameTexture> tex)override;

  //=============================================================================================
  //                              Getter / Setter
  //=============================================================================================
    const std::vector<int>& GetDrawMapData() const override { return mapdata; } //�}�b�v�`�b�v��int�z���getter
    void SetDrawMapData(std::vector<int> copyvector) { mapdata = copyvector; }  //�}�b�v�`�b�v��int�z���setter


    //=============================================================================================
    //                              �f�X�g���N�^
    //=============================================================================================
    ~TestMapManager() = default;
private:
    int currentnumber;			    //���݂̃X�e�[�W�ԍ����L������
    int currentpartition;			//�X�e�[�W�𕪊��������Ō��݂͉��Ԗڂ�������
    
    std::shared_ptr<GameTexture> mapchip;
    std::vector<int> backmap;
    std::vector<int> mapdata;
    
    MapStatus primarymap;
    MapStatus secondarymap;

    std::shared_ptr< SpriteRenderer> render_;

    void MapDataUpdate(MapStatus& map,int startprogress);       //�`�ʂ���}�b�v�̔z����X�V����
};



#endif //TestMapManager_H