#ifndef MANAGEFRAME_H
#define MANAGEFRAME_H

#include <QFrame>
// QFrame 상속 받고 함수 오버라이딩 하여  protected 함수 참조
class ManageFrame : public QFrame {
    Q_OBJECT

private:
    static const QMap<int, QString> imagePaths; // 프레임 번호와 이미지 경로 매핑

public:
    explicit ManageFrame(QWidget *parent = nullptr);
    QPixmap getImage(int n) const; //이미지 반환 함수

protected:
    void mousePressEvent(QMouseEvent * event) override;

signals:
    void frameClicked();
};

#endif // MANAGEFRAME_H
