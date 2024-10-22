/* Create the database */
CREATE DATABASE IF NOT EXISTS SandwichInfo;

/* Switch to the classicmodels database */
USE SandwichInfo;

DROP TABLE IF EXISTS Price;
DROP TABLE IF EXISTS Detail;
DROP TABLE IF EXISTS Sandwich;
DROP TABLE IF EXISTS Bread;
DROP TABLE IF EXISTS Topping;
DROP TABLE IF EXISTS Cheese;
DROP TABLE IF EXISTS Vegetable;
DROP TABLE IF EXISTS Sauce;
DROP TABLE IF EXISTS Cookie;
DROP TABLE IF EXISTS Drink;
DROP TABLE IF EXISTS Chips;

CREATE TABLE Price(
	SandName TEXT,
	_15cm INT,
    _30cm INT
);

CREATE TABLE Detail(
	SandNameEn TEXT,
	SandNameKr TEXT,
	Kcal INT,
    Protein FLOAT,
    SatFat FLOAT,
    Sugar FLOAT,
    Nat INT,
    Expln TEXT
);

CREATE TABLE Sandwich(
	SandName TEXT
);

CREATE TABLE Bread(
	BreadName TEXT
);

CREATE TABLE Topping(
	ToppingName TEXT
);

CREATE TABLE Cheese(
	CheeseName TEXT
);

CREATE TABLE Vegetable(
	VegetableName TEXT
);

CREATE TABLE Sauce(
	SauceName TEXT
);

CREATE TABLE Cookie(
	CookieName TEXT
);

CREATE TABLE Drink(
	DrinkName TEXT
);

CREATE TABLE Chips(
	ChipsName TEXT
);

/* 가격 정보 입력 */
INSERT INTO Price (SandName, _15cm, _30cm) VALUES('에그마요', 5500, 10400);
INSERT INTO Price (SandName, _15cm, _30cm) VALUES('햄', 5800, 10900);
INSERT INTO Price (SandName, _15cm, _30cm) VALUES('참치', 5800, 10900);
INSERT INTO Price (SandName, _15cm, _30cm) VALUES('BLT', 6600, 12200);
INSERT INTO Price (SandName, _15cm, _30cm) VALUES('이탈리안BMT', 6700, 12400);
INSERT INTO Price (SandName, _15cm, _30cm) VALUES('베지', 4900, 9100);
INSERT INTO Price (SandName, _15cm, _30cm) VALUES('치킨슬라이스', 6500, 12000);
INSERT INTO Price (SandName, _15cm, _30cm) VALUES('써브웨이클럽', 7100, 13100);
INSERT INTO Price (SandName, _15cm, _30cm) VALUES('로티세리바비큐치킨', 7300, 13500);
INSERT INTO Price (SandName, _15cm, _30cm) VALUES('로스트치킨', 7300, 13500);
INSERT INTO Price (SandName, _15cm, _30cm) VALUES('치킨테리야키', 7000, 12900);
INSERT INTO Price (SandName, _15cm, _30cm) VALUES('스파이시이탈리안', 6900, 12700);
INSERT INTO Price (SandName, _15cm, _30cm) VALUES('풀드포크바비큐', 7200, 13300);
INSERT INTO Price (SandName, _15cm, _30cm) VALUES('스테이크앤치즈', 7900, 14700);
INSERT INTO Price (SandName, _15cm, _30cm) VALUES('치킨베이컨아보카도', 7900, 14700);
INSERT INTO Price (SandName, _15cm, _30cm) VALUES('새우', 7600, 13100);
INSERT INTO Price (SandName, _15cm, _30cm) VALUES('코리안바비큐', 7300, 13500);
INSERT INTO Price (SandName, _15cm, _30cm) VALUES('스파이시새우', 7900, 13100);
INSERT INTO Price (SandName, _15cm, _30cm) VALUES('랍스터', 16900, 33800);
INSERT INTO Price (SandName, _15cm, _30cm) VALUES('랍스터반새우반', 13900, 27800);
INSERT INTO Price (SandName, _15cm, _30cm) VALUES('비프앤머쉬룸', 8600, 17200);
INSERT INTO Price (SandName, _15cm, _30cm) VALUES('비프', 10400, 20800);

/* 메뉴별 상세 정보 입력 */
/* 메뉴별 상세 정보 입력 */
INSERT INTO Detail (SandNameEn, SandNameKr, Kcal, Protein, SatFat, Sugar, Nat, Expln) 
VALUES('EggMayo', '에그마요', 416, 16.4, 4.8, 7.7, 554, '속재료 - 에그마요 2스쿱추천 소스 조합 - 랜치 + 핫 칠리(또는 스위트 칠리)삶은 계란을 다져서 마요네즈에 버무린 것을 얹는다. 저렴하면서도 양이 꽤나 풍부하다. 그래서인지 서브웨이 메뉴판에 베스트 메뉴로 표시될 만큼 꽤 인기 있다. 마요네즈 때문인지 칼로리는 상당한 편. 페퍼로니나 베이컨을 추가하면 더 맛있어진다.');

INSERT INTO Detail (SandNameEn, SandNameKr, Kcal, Protein, SatFat, Sugar, Nat, Expln) 
VALUES('Ham', '햄', 262, 19, 1, 8.4, 680, '속재료 - 블랙포레스트햄 4장추천 소스 조합 - 랜치(또는 마요네즈) + 허니 머스타드써브웨이 샌드위치의 가장 기본적인 구성을 보여준다. 가장 무난하며 가격 대비 만족도가 높은 메뉴. 햄의 양이 꽤 돼서 더블미트를 하면 야채보다 햄의 두께가 더 두꺼워질 정도이다.');

INSERT INTO Detail (SandNameEn, SandNameKr, Kcal, Protein, SatFat, Sugar, Nat, Expln) 
VALUES('Tuna', '참치', 316, 26.9, 1.4, 7.6, 535, '속재료 - 참치 2스쿱추천 소스 조합 - 홀스래디쉬 + 스위트 어니언마요네즈에 버무린 통조림 참치를 넣어준다. 지방 함량이 써브웨이 샌드위치 중 가장 높은 축에 속했다. 15cm 기준 29.8그램.그런데 영양성분표가 바뀌면서 최고 칼로리 메뉴에서 뜬금없이 로스트치킨급의 고단백 저칼로리 메뉴(480->316kcal, 단백질 26.9g)가 되었다. 이는 본사에서 제공하는 참치와 매장에서 제조할 때 마요네즈 비율이 바뀌었다고 한다.');

INSERT INTO Detail (SandNameEn, SandNameKr, Kcal, Protein, SatFat, Sugar, Nat, Expln) 
VALUES('BLT', 'B.L.T', 300, 15.9, 3.7, 7.9, 666, '속재료 - 베이컨 4장추천 소스 조합 - 랜치 + 스위트 칠리기본 채소와 치즈에 베이컨 4장을 얹어 주는 메뉴다. 베이컨이 훈제햄보다 맛이 강한 관계로 의외로 푸짐한 맛이 난다. B.L.T.란 베이컨(Bacon), 양상추(Lettuce), 토마토(Tomato)의 앞 글자를 딴 것으로 실제 BLT 샌드위치[30]와 동일하진 않다. BMT와 헷갈리지 않게 주의하자. 알바도 가끔 헷갈린다. 심지어 가격까지 같다. 몇몇 매장에서는 메뉴에 써진 번호로 말해달라고 한다.');

INSERT INTO Detail (SandNameEn, SandNameKr, Kcal, Protein, SatFat, Sugar, Nat, Expln) 
VALUES('ItalianBMT', '이탈리안BMT', 388, 21, 5.9, 8.6, 1064, '속재료 - 페퍼로니 3장, 살라미 3장, 햄 2장추천 소스 조합 - 랜치 + 허니 머스타드 (홀스래디쉬 + 스위트 어니언 조합도 수요가 있는 편.)서브웨이 부동의 베스트메뉴 1위이며, 비록 가공육이지만 육류가 가장 많이 들어가는 메뉴이다. BLT나 햄보다 고기 맛을 더 강화하고 싶다면 추천하는 메뉴다. 살라미와 페퍼로니의 짭짤하고 매콤한 맛에 햄의 육향이 더해진 맛이 일품. BMT에서 햄 빼고 페퍼로니와 살라미를 더 넣으면 짜디 짠 스파이시 이탈리안이 나온다.');

INSERT INTO Detail (SandNameEn, SandNameKr, Kcal, Protein, SatFat, Sugar, Nat, Expln) 
VALUES('Veggie', '베지', 209, 9.2, 0.6, 7.6, 262, '속재료 - 없음(기본 야채와 치즈만 들어감)추천 소스 조합 - 올리브 오일 + 소금 + 후추(+ 레드와인 식초), 근데 야채만 들어간다는 점이 오히려 어떤 소스를 넣어도 평균 이상의 값은 해준다. 칠리 종류만 아니라면 좋아하는 소스 아무거나 넣어도 OK.빵에 야채와 소스만 들어가는 샌드위치. 그래서 가격이 싸다. 소스를 아예 안 넣거나, 오일과 식초를 골라서 넣거나 이탈리안 드레싱을 선택하면 괜찮은 다이어트 식단이 된다. 비건의 경우 화이트나 하티에 치즈 빼고 소스는 스위트 어니언이나 올리브 오일이나 레드 와인 식초를 넣으면 비건이다. 아보카도를 추가해도 잘 어울린다. 오믈렛을 추가하고 야채를 있는데로 추가하면 5400원에 정말 푸짐하게 단백질까지 먹을 수 있다.');

INSERT INTO Detail (SandNameEn, SandNameKr, Kcal, Protein, SatFat, Sugar, Nat, Expln) 
VALUES('ChickenSlice', '치킨슬라이스', 265, 18.6, 0.9, 8.7, 751, '속재료 - 치킨 슬라이스 4장추천 소스 조합 - 랜치+스위트 어니언터키 대체로 나온 메뉴이며 베지 다음으로 다이어트에 좋은 메뉴. 보다 적은 칼로리로 단백질까지 얻을 수 있다는 점에서 베지보다 더 나을 수도 있다.');

INSERT INTO Detail (SandNameEn, SandNameKr, Kcal, Protein, SatFat, Sugar, Nat, Expln) 
VALUES('SubwayClub', '써브웨이클럽', 293, 19.5, 2.4, 8.5, 773, '속재료 - 치킨 슬라이스 2장, 햄 1장, 베이컨 2장 추천 소스 조합 - 랜치 + 스위트 칠리서브웨이에서 상당히 밀어주는 메뉴로서 잘 알려지진 않았지만 속재료의 밸런스가 잘 맞는 메뉴다. 야채를 조금 적게 넣는 것이 속재료의 맛을 느끼기에 좋다.');

INSERT INTO Detail (SandNameEn, SandNameKr, Kcal, Protein, SatFat, Sugar, Nat, Expln) 
VALUES('RotiserieBBQChicken', '로티세리바비큐치킨', 327, 29.1, 2.5, 7.8, 542, '속재료 - 로티세리 치킨 1스쿱추천 소스 조합 - 랜치 + 허니 머스타드(치킨이 들어가는 메뉴엔 보통 허니 머스타드가 잘 어울린다.)닭가슴살 구이 하나가 덩어리로 들어가는 로스트 치킨과 달리 잘게 찢은 치킨을 한 스쿱 떠서 넣는 샌드위치. 2021년 10월 부로 원재료를 생산하는 닭공장에서 문제가 생겨 잠정 품절되었다. 동년 11월부터 업체를 바꾸어 다시 판매 재개했다.');

INSERT INTO Detail (SandNameEn, SandNameKr, Kcal, Protein, SatFat, Sugar, Nat, Expln) 
VALUES('RoastedChicken', '로스트치킨', 300, 26, 1.3, 8.7, 605, '속재료 - 치킨 브레스트 1개추천 소스 조합 - 랜치 + 허니 머스타드구운 닭가슴살이 덩어리로 들어가는 샌드위치. 지방과 나트륨이 적고 단백질이 풍부한 닭가슴살이 들어가기 때문에 이것 역시 소스만 잘 선택한다면 좋은 다이어트 식단이 된다. 사진으로 보기에는 닭가슴살이 통으로 들어가는 것으로 보이나, 실제로는 굵게 다져진 가슴살로 만든 패티이다. 이미 한번 조리된 상태로 냉동되어 각 지점에 입고가 되며, 이를 해동하여 빵과 함께 토스팅 해 준다. 패티가 두툼하고 빡빡하지도 않아서 수제 치킨버거 느낌이 난다.');

INSERT INTO Detail (SandNameEn, SandNameKr, Kcal, Protein, SatFat, Sugar, Nat, Expln) 
VALUES('ChickenTeriyaki', '치킨테리야키', 314, 26.5, 1.2, 10.1, 698, '속재료 - 치킨 데리야끼 1스쿱추천 소스 조합 - 스위트 어니언 + 스모크 바베큐(+ 랜치)데리야끼 소스에 절인 닭가슴살이 들어간다. 고기 맛이 강하면서도 열량이 높지 않고 나트륨도 적은 편이라 다이어트 메뉴로 좋다. 진짜 다이어트를 원하면 로스트 치킨이 더 좋긴 한데 비싸다. 허니 머스타드와도 잘 어울린다. 원래 스위트 어니언 치킨 데리야키라는 이름이었던 만큼 스위트 어니언 소스와는 찰떡궁합이다.');

INSERT INTO Detail (SandNameEn, SandNameKr, Kcal, Protein, SatFat, Sugar, Nat, Expln) 
VALUES('SpicyItalian', '스파이시이탈리안', 464, 20.7, 9.1, 8.7, 1250, '속재료 - 페퍼로니 5장, 살라미 5장추천 소스 조합 - 핫 칠리(스위트 칠리) + 랜치 + 마요네즈(또는 홀스래디쉬)살라미 5장과 페퍼로니 5장, 총 10장이나 들어가는 만큼 칼로리도 높고 나트륨이 1,490mg으로 매우 높다. 이탈리안 BMT의 변형 버전. 일반적인 한국인 입맛에는 상당히 짜게 느껴질 수 있으니 야채를 충분히 추가하는 게 좋다. 소스를 조금만 넣는 것도 방법.');

INSERT INTO Detail (SandNameEn, SandNameKr, Kcal, Protein, SatFat, Sugar, Nat, Expln) 
VALUES('PulledPorkBBQ', '풀드포크바비큐', 327, 24.8, 2.1, 7.8, 689, '속재료 - 풀드포크 1스쿱추천 소스 조합 - 스모크 바베큐 + 랜치돼지고기를 얇게 찢어내어 각종 양념을 첨가해 훈제로 익힌 다음 바베큐 소스를 기본으로 넣어주는 샌드위치. 2010년대 들어서 미국에서 특별 메뉴로 첫 선을 보였으며 이후 유럽 및 호주 지역에도 판매 중. 특이 사항으로, 캐나다에서는 한국식으로 매운 양념을 넣어 "코리안 BBQ 풀드 포크"라는 변종 메뉴를 판매 중이다. 호불호가 갈리는데 얇게 찢어낸 고기를 훈제로 짭조름하게 조려낸 것이라 식감이 장조림 같다고 혹평하는 사람도 제법 있다.');

INSERT INTO Detail (SandNameEn, SandNameKr, Kcal, Protein, SatFat, Sugar, Nat, Expln) 
VALUES('Staek_Cheese', '스테이크앤치즈', 355, 28.1, 4.2, 8.8, 780, '속재료 - 스테이크 1스쿱추천 소스 조합 - 스모크 바베큐 + 스위트 어니언(마요네즈)찹스테이크와 치즈가 들어가는 샌드위치. 첫 맛이 국물 없는 쇠고기 장조림과 비슷하다. 머스타드 소스를 조금 넣는 것도 괜찮다. 칼로리가 높아 보이지만 메뉴 이름에 치즈가 들어가는 관계로 치즈 칼로리(약 40Kcal)가 포함되어 있지만 의외로 다이어트에 나쁘지 않은 메뉴이다.하지만 비싸다');

INSERT INTO Detail (SandNameEn, SandNameKr, Kcal, Protein, SatFat, Sugar, Nat, Expln) 
VALUES('ChickenBaconAvocado', '치킨베이컨아보카도', 349, 19.9, 3.2, 9, 860, '속재료 - 치킨 슬라이스 3장, 베이컨 2장, 아보카도 1스쿱추천 소스 조합 - 랜치(사우스웨스트) + 스위트 어니언아보카도 과카몰리가 들어가는 샌드위치. 매장에 따라 더 비싼 것 같기도 하다.');

INSERT INTO Detail (SandNameEn, SandNameKr, Kcal, Protein, SatFat, Sugar, Nat, Expln) 
VALUES('Shrimp', '새우', 229, 13.6, 0.6, 7.8, 357, '속재료 - 새우 5마리추천 소스 조합 - 스위트 칠리 + 마요네즈(후추)기간 한정 메뉴였으나 정식 메뉴로 승격되었다. 2023년 들어서 새우의 크기가 이전보다 커졌다.');

INSERT INTO Detail (SandNameEn, SandNameKr, Kcal, Protein, SatFat, Sugar, Nat, Expln) 
VALUES('KBBQ', '코리안바비큐', 372, 25.6, 2.1, 14.7, 899, '속재료 - K-BBQ 소스를 버무린 풀드포크 바비큐 1스쿱추천 소스 조합 - 올리브 오일 + 후추풀드포크에 간장 및 마늘 베이스로 불고기 양념을 한 메뉴이다. 양념이 한번 된 메뉴이기 때문에 어떤 소스를 넣던 간에 짜게 느껴질 수 있으니 주의. 2020년 10월부터 판매하기 시작해 상당히 많은 매니아층을 보유하게 되었다.');

INSERT INTO Detail (SandNameEn, SandNameKr, Kcal, Protein, SatFat, Sugar, Nat, Expln) 
VALUES('SpicyShrimp', '스파이시새우', 245, 16.5, 0.9, 9.1, 570, '속재료 - 스파이시 새우 5마리추천 소스 조합 - 올리브 오일여름 한정 스페셜 메뉴. 동남아 풍의 매운 양념을 바른 새우가 들어있다. 매년 주기적으로 출시한다. 2023년 들어서 새우의 크기가 이전보다 커졌다.');

INSERT INTO Detail (SandNameEn, SandNameKr, Kcal, Protein, SatFat, Sugar, Nat, Expln) 
VALUES('Lobster', '랍스터', 320, 20.4, 1.8, 7.8, 578, '');

INSERT INTO Detail (SandNameEn, SandNameKr, Kcal, Protein, SatFat, Sugar, Nat, Expln) 
VALUES('HalfLobster_HalfShrimp', '랍스터반새우반', 284, 18.8, 1.2, 7.9, 578, '');

INSERT INTO Detail (SandNameEn, SandNameKr, Kcal, Protein, SatFat, Sugar, Nat, Expln) 
VALUES('Beef_Mushroom', '비프앤머쉬룸', 292, 16.5, 2.5, 8, 598, '...');

INSERT INTO Detail (SandNameEn, SandNameKr, Kcal, Protein, SatFat, Sugar, Nat, Expln) 
VALUES('Beef', '비프', 342, 21.6, 4.6, 8.3, 830, '...');



/* 빵 이름 입력 */
INSERT INTO Bread (BreadName) VALUES('위트');
INSERT INTO Bread (BreadName) VALUES('허니 오트');
INSERT INTO Bread (BreadName) VALUES('화이트');
INSERT INTO Bread (BreadName) VALUES('하티 이탈리안');
INSERT INTO Bread (BreadName) VALUES('파마산 오레가노');
INSERT INTO Bread (BreadName) VALUES('플랫 브레드');

/* 토핑 이름 입력 */
INSERT INTO Topping (ToppingName) VALUES('새우');
INSERT INTO Topping (ToppingName) VALUES('에그마요');
INSERT INTO Topping (ToppingName) VALUES('오믈렛');
INSERT INTO Topping (ToppingName) VALUES('아보카도');
INSERT INTO Topping (ToppingName) VALUES('페퍼로니');
INSERT INTO Topping (ToppingName) VALUES('베이컨');
INSERT INTO Topping (ToppingName) VALUES('더블미트');

/* 치즈 이름 입력 */
INSERT INTO Cheese (CheeseName) VALUES('아메리칸 치즈');
INSERT INTO Cheese (CheeseName) VALUES('슈레드 치즈');
INSERT INTO Cheese (CheeseName) VALUES('모짜렐라 치즈');

/* 야채 이름 입력 */
INSERT INTO Vegetable (VegetableName) VALUES('양배추');
INSERT INTO Vegetable (VegetableName) VALUES('오이');
INSERT INTO Vegetable (VegetableName) VALUES('토마토');
INSERT INTO Vegetable (VegetableName) VALUES('양파');
INSERT INTO Vegetable (VegetableName) VALUES('피망');
INSERT INTO Vegetable (VegetableName) VALUES('피클');
INSERT INTO Vegetable (VegetableName) VALUES('할라피뇨');
INSERT INTO Vegetable (VegetableName) VALUES('올리브');

/* 소스 이름 입력 */
INSERT INTO Sauce (SauceName) VALUES('마요네즈');
INSERT INTO Sauce (SauceName) VALUES('렌치');
INSERT INTO Sauce (SauceName) VALUES('머스타드');
INSERT INTO Sauce (SauceName) VALUES('홀스 레디시');
INSERT INTO Sauce (SauceName) VALUES('사우스 웨스트 치폴레');
INSERT INTO Sauce (SauceName) VALUES('핫칠리');
INSERT INTO Sauce (SauceName) VALUES('스모크 바베큐');
INSERT INTO Sauce (SauceName) VALUES('스위트 칠리');
INSERT INTO Sauce (SauceName) VALUES('허니머스타드');
INSERT INTO Sauce (SauceName) VALUES('스위트 어니언');
INSERT INTO Sauce (SauceName) VALUES('소금');
INSERT INTO Sauce (SauceName) VALUES('후추');
INSERT INTO Sauce (SauceName) VALUES('올리브오일');
INSERT INTO Sauce (SauceName) VALUES('레드와인 식초');

/* 쿠키 이름 입력 */
INSERT INTO Cookie (CookieName) VALUES('오트밀레이즌');
INSERT INTO Cookie (CookieName) VALUES('화이트 초코 마카다미아');
INSERT INTO Cookie (CookieName) VALUES('라즈베리치즈케이크');
INSERT INTO Cookie (CookieName) VALUES('초코칩');
INSERT INTO Cookie (CookieName) VALUES('더블초코칩');

/* 음료 이름 입력 */
INSERT INTO Drink (DrinkName) VALUES('콜라');
INSERT INTO Drink (DrinkName) VALUES('사이다');
INSERT INTO Drink (DrinkName) VALUES('환타');

/* 감자칩 이름 입력 */
INSERT INTO Chips (ChipsName) VALUES('포카칩');
INSERT INTO Chips (ChipsName) VALUES('스윙칩');
INSERT INTO Chips (ChipsName) VALUES('나초');
INSERT INTO Chips (ChipsName) VALUES('프링글스');
INSERT INTO Chips (ChipsName) VALUES('오감자');

SELECT * from Bread;
SELECT * FROM Topping;
SELECT * FROM Cheese;
SELECT * FROM Vegetable;
SELECT * FROM Sauce;
SELECT * FROM Cookie;
SELECT * FROM Drink;
SELECT * FROM Chips;

#SELECT * from Price;
#Select * from Detail;