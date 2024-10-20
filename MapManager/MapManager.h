#ifndef MAPMANAGER_H
#define MAPMANAGER_H



class GameTexture;
#include <iostream>
#include <vector>
#include <string>
#include "types.h"

#include "GameTexture.h" 
#include "IMapManager.h"


class MapManager : public IMapManager {
public:
    //=============================================================================================
    //                              �R���X�g���N�^
    //=============================================================================================
    MapManager() : currentnumber(0), currentpartition(0),
        mapchip(0), mapdata({}), backmap({}),
        primarymap({ false, {}, 0, 0 }),
        secondarymap({ false, {},0,0 })
    {
        mapmanager_->LoadMapChipTexture(rm->GetTextureManager()->GetTexture(TextureType::Map));     //�}�b�v�`�b�v�̃��[�h
        mapmanager_->SetDrawMapData(rm->ConvertDrawMapCsv_Vector());

        //mapmanager_->LoadFrontMapDataCsv(rm->Getmapcsv(ScopeMapData::frontmap));                    //�t�����g�}�b�v��csv
        //mapmanager_->LoadBackMapDataCsv(rm->Getmapcsv(ScopeMapData::backmap));                      //�o�b�N�}�b�v��csv

    }
    //=============================================================================================
    //                              �f�X�g���N�^
    //=============================================================================================
    ~MapManager() = default;

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

    std::shared_ptr<GameTexture> mapchip;       //�}�b�v�`�b�v�̉摜��ۊǂ��Ă����ϐ�
    std::vector<int> backmap;               
    std::vector<int> mapdata;           //�}�b�v�`�b�v�̔z�u���Ǘ�����int�z��

    MapStatus primarymap;       //���������}�b�v�f�[�^��ێ����Ă����ϐ�
    MapStatus secondarymap;     //���������}�b�v�f�[�^��ێ����Ă����ϐ�

    void MapDataUpdate(MapStatus& map, int startprogress);       //�`�ʂ���}�b�v�̔z����X�V����
};




#endif //MAPMANAGER_H