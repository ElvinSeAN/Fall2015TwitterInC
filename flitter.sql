

CREATE TABLE account(
	uid BIGINT AUTO_INCREMENT PRIMARY KEY,
	password VARCHAR(30) NOT NULL
	);

CREATE TABLE flitters (
	uid BIGINT	NOT NULL,
	fname VARCHAR(50) NOT NULL,
	lname VARCHAR(50) NOT NULL,
	location VARCHAR(50),
		FOREIGN KEY (uid) REFERENCES account(uid)
	);

CREATE TABLE fleets(
	pid BIGINT AUTO_INCREMENT PRIMARY KEY,
	post VARCHAR(155) NOT NULL,
	uid BIGINT NOT NULL,
		FOREIGN KEY (uid) REFERENCES account(uid)

		);
CREATE TABLE follows(
	head BIGINT NOT NULL,
	follower BIGINT NOT NULL,
		FOREIGN KEY (head) REFERENCES account(uid),
		FOREIGN KEY (follower)	REFERENCES account(uid),
		PRIMARY KEY (head,follower)
		);

CREATE TABLE refleet(
	repid BIGINT AUTO_INCREMENT PRIMARY KEY,
	rpost VARCHAR(155)	NOT NULL,
	pid BIGINT NOT NULL,
	uid	BIGINT NOT NULL, 
		FOREIGN KEY(uid) REFERENCES account(uid),
		FOREIGN KEY(pid) REFERENCES fleets(pid)
);