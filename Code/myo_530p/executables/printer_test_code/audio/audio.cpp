/*
 * audio.cpp
 *
 *  Created on: Aug 19, 2016
 *      Author: Holguer
 */

#include "audio.h"
extern "C" {
#include "../fpga_ports/fpga_ports.h"
}

audio::audio() {
	// TODO Auto-generated constructor stub
	this->baseport = NULL;
}

audio::audio(unsigned int address) {
	this->baseport = open_lw(address);
}

void audio::set_frequency(unsigned int freq) {
	if (freq == 0) {
		return;
	}
	*(unsigned int *) this->baseport = (unsigned int) (50000000 / (2 * freq))
			- 1;
}

void audio::sleep(unsigned int milliseconds) {
	usleep(milliseconds * 800);
}

void audio::Beep(int freq, int millseconds) {
	set_frequency(freq * 5);
	this->sleep(millseconds);
	set_frequency(0);
}

void audio::jingle_bells() {
	this->refrenSolo();
	this->coupleSolo();
	this->refrenSolo();
}

void audio::refrenSolo() {
	this->Beep(E5, half);
	this->Beep(E5, half);
	this->Beep(E5, half);

	this->sleep(half);

	this->Beep(E5, half);
	this->Beep(E5, half);
	this->Beep(E5, half);

	this->sleep(half);

	this->Beep(E5, half);
	this->Beep(G5, half);
	this->Beep(C5, half);
	this->Beep(D5, half);
	this->Beep(E5, half);

	this->Beep(C4, half);
	this->Beep(D4, half);
	this->Beep(E4, half);

	this->Beep(F5, half);
	this->Beep(F5, half);
	this->Beep(F5, half);

	this->sleep(half);

	this->Beep(F5, half);
	this->Beep(E5, half);
	this->Beep(E5, half);

	this->sleep(half);

	this->Beep(E5, half);
	this->Beep(D5, half);
	this->Beep(D5, half);
	this->Beep(E5, half);
	this->Beep(D5, half);

	this->sleep(half);

	this->Beep(G5, half);

	this->sleep(half);

// -----------

	this->Beep(E5, half);
	this->Beep(E5, half);
	this->Beep(E5, half);

	this->sleep(half);

	this->Beep(E5, half);
	this->Beep(E5, half);
	this->Beep(E5, half);

	this->sleep(half);

	this->Beep(E5, half);
	this->Beep(G5, half);
	this->Beep(C5, half);
	this->Beep(D5, half);
	this->Beep(E5, half);

	this->Beep(C4, half);
	this->Beep(D4, half);
	this->Beep(E4, half);

	this->Beep(F5, half);
	this->Beep(F5, half);
	this->Beep(F5, half);

	this->sleep(half);

	this->Beep(F5, half);
	this->Beep(E5, half);
	this->Beep(E5, half);

	this->sleep(half);

	this->Beep(G5, half);
	this->Beep(G5, half);
	this->Beep(F5, half);
	this->Beep(D5, half);
	this->Beep(C5, full);

	this->sleep(full);

	this->set_frequency(200000);
}

void audio::coupleSolo() {
	this->Beep(G4, half);
	this->Beep(E5, half);
	this->Beep(D5, half);
	this->Beep(C5, half);
	this->Beep(G4, full);

	this->sleep(half * 2);

	this->Beep(G4, half);
	this->Beep(E5, half);
	this->Beep(D5, half);
	this->Beep(C5, half);
	this->Beep(A4, full);

	this->sleep(full);

	this->Beep(A4, half);
	this->Beep(F5, half);
	this->Beep(E5, half);
	this->Beep(D5, half);
	this->Beep(G5, full);

	this->sleep(full);

	this->Beep(A5, half);
	this->Beep(A5, half);
	this->Beep(G5, half);
	this->Beep(Eb5, half);
	this->Beep(E5, full);

	this->sleep(full);

// -----------

	this->Beep(G4, half);
	this->Beep(E5, half);
	this->Beep(D5, half);
	this->Beep(C5, half);
	this->Beep(G4, full);

	this->sleep(full);

	this->Beep(G4, half);
	this->Beep(E5, half);
	this->Beep(D5, half);
	this->Beep(C5, half);
	this->Beep(A4, full);

	this->sleep(full);

	this->Beep(A4, half);
	this->Beep(F5, half);
	this->Beep(E5, half);
	this->Beep(D5, half);
	this->Beep(G5, full);

	this->sleep(full);

	this->Beep(A5, half);
	this->Beep(G5, half);
	this->Beep(F5, half);
	this->Beep(D5, half);
	this->Beep(C5, full);

	this->sleep(full);

	this->set_frequency(200000);

}

// ------------------------------------------------------------------- Bass Line

void audio::star_wars_song() {

	this->Beep(440, 500);
	this->Beep(440, 500);
	this->Beep(440, 500);
	this->Beep(349, 350);
	this->Beep(523, 150);
	this->Beep(440, 500);
	this->Beep(349, 350);
	this->Beep(523, 150);
	this->Beep(440, 1000);
	this->Beep(659, 500);
	this->Beep(659, 500);
	this->Beep(659, 500);
	this->Beep(698, 350);
	this->Beep(523, 150);
	this->Beep(415, 500);
	this->Beep(349, 350);
	this->Beep(523, 150);
	this->Beep(440, 1000);

	this->set_frequency(200000);

}

void audio::test_mario_song() {
	this->Beep(1480, 200);

	this->Beep(1568, 200);

	this->Beep(1568, 200);

	this->Beep(1568, 200);

	this->Beep(739.99, 200);

	this->Beep(783.99, 200);

	this->Beep(783.99, 200);

	this->Beep(783.99, 200);

	this->Beep(369.99, 200);

	this->Beep(392, 200);

	this->Beep(369.99, 200);

	this->Beep(392, 200);

	this->Beep(392, 400);

	this->Beep(196, 400);

	this->Beep(739.99, 200);

	this->Beep(783.99, 200);

	this->Beep(783.99, 200);

	this->Beep(739.99, 200);

	this->Beep(783.99, 200);

	this->Beep(783.99, 200);

	this->Beep(739.99, 200);

	this->Beep(783.99, 200);

	this->Beep(880, 200);

	this->Beep(830.61, 200);

	this->Beep(880, 200);

	this->Beep(987.77, 400);

	this->Beep(880, 200);

	this->Beep(783.99, 200);

	this->Beep(698.46, 200);

	this->Beep(739.99, 200);

	this->Beep(783.99, 200);

	this->Beep(783.99, 200);

	this->Beep(739.99, 200);

	this->Beep(783.99, 200);

	this->Beep(783.99, 200);

	this->Beep(739.99, 200);

	this->Beep(783.99, 200);

	this->Beep(880, 200);

	this->Beep(830.61, 200);

	this->Beep(880, 200);

	this->Beep(987.77, 400);

	this->sleep(200);

	this->Beep(1108, 10);
	this->Beep(1174.7, 200);
	this->Beep(1480, 10);
	this->Beep(1568, 200);

	this->sleep(200);
	this->Beep(739.99, 200);

	this->Beep(783.99, 200);

	this->Beep(783.99, 200);

	this->Beep(739.99, 200);

	this->Beep(783.99, 200);

	this->Beep(783.99, 200);

	this->Beep(739.99, 200);

	this->Beep(783.99, 200);

	this->Beep(880, 200);

	this->Beep(830.61, 200);

	this->Beep(880, 200);

	this->Beep(987.77, 400);

	this->Beep(880, 200);

	this->Beep(783.99, 200);

	this->Beep(698.46, 200);

	this->Beep(659.25, 200);

	this->Beep(698.46, 200);

	this->Beep(784, 200);

	this->Beep(880, 400);

	this->Beep(784, 200);

	this->Beep(698.46, 200);

	this->Beep(659.25, 200);

	this->Beep(587.33, 200);

	this->Beep(659.25, 200);

	this->Beep(698.46, 200);

	this->Beep(784, 400);

	this->Beep(698.46, 200);

	this->Beep(659.25, 200);

	this->Beep(587.33, 200);

	this->Beep(523.25, 200);

	this->Beep(587.33, 200);

	this->Beep(659.25, 200);

	this->Beep(698.46, 400);

	this->Beep(659.25, 200);

	this->Beep(587.33, 200);

	this->Beep(493.88, 200);

	this->Beep(523.25, 200);

	this->sleep(400);
	this->Beep(349.23, 400);

	this->Beep(392, 200);

	this->Beep(329.63, 200);

	this->Beep(523.25, 200);

	this->Beep(493.88, 200);

	this->Beep(466.16, 200);

	this->Beep(440, 200);

	this->Beep(493.88, 200);

	this->Beep(523.25, 200);

	this->Beep(880, 200);

	this->Beep(493.88, 200);

	this->Beep(880, 200);

	this->Beep(1760, 200);

	this->Beep(440, 200);

	this->Beep(392, 200);

	this->Beep(440, 200);

	this->Beep(493.88, 200);

	this->Beep(783.99, 200);

	this->Beep(440, 200);

	this->Beep(783.99, 200);

	this->Beep(1568, 200);

	this->Beep(392, 200);

	this->Beep(349.23, 200);

	this->Beep(392, 200);

	this->Beep(440, 200);

	this->Beep(698.46, 200);

	this->Beep(415.2, 200);

	this->Beep(698.46, 200);

	this->Beep(1396.92, 200);

	this->Beep(349.23, 200);

	this->Beep(329.63, 200);

	this->Beep(311.13, 200);

	this->Beep(329.63, 200);

	this->Beep(659.25, 200);

	this->Beep(698.46, 400);

	this->Beep(783.99, 400);

	this->Beep(440, 200);

	this->Beep(493.88, 200);

	this->Beep(523.25, 200);

	this->Beep(880, 200);

	this->Beep(493.88, 200);

	this->Beep(880, 200);

	this->Beep(1760, 200);

	this->Beep(440, 200);

	this->Beep(392, 200);

	this->Beep(440, 200);

	this->Beep(493.88, 200);

	this->Beep(783.99, 200);

	this->Beep(440, 200);

	this->Beep(783.99, 200);

	this->Beep(1568, 200);

	this->Beep(392, 200);

	this->Beep(349.23, 200);

	this->Beep(392, 200);

	this->Beep(440, 200);

	this->Beep(698.46, 200);

	this->Beep(659.25, 200);

	this->Beep(698.46, 200);

	this->Beep(739.99, 200);

	this->Beep(783.99, 200);

	this->Beep(392, 200);

	this->Beep(392, 200);

	this->Beep(392, 200);

	this->Beep(392, 200);

	this->Beep(196, 200);

	this->Beep(196, 200);

	this->Beep(196, 200);

	this->Beep(185, 200);

	this->Beep(196, 200);

	this->Beep(185, 200);

	this->Beep(196, 200);

	this->Beep(207.65, 200);

	this->Beep(220, 200);

	this->Beep(233.08, 200);

	this->Beep(246.94, 200);


	this->set_frequency(200000);
}

void audio::happy_birthday() {
	unsigned FREQUENCY[] =
			{ 392, 392, 440, 392, 523, 494, 392, 392, 440, 392, 587, 523, 392,
					392, 784, 659, 523, 494, 440, 689, 689, 523, 587, 523 };
	unsigned DELAY[] = { 375, 125, 500, 500, 500, 1000, 375, 125, 500, 500, 500,
			1000, 375, 125, 500, 500, 500, 500, 1000, 375, 125, 500, 500, 500,
			1000 };
	int CIRCLE;
	for (CIRCLE = 0; CIRCLE < 25; CIRCLE++) {
		this->Beep(FREQUENCY[CIRCLE], DELAY[CIRCLE]);
	}

	this->set_frequency(200000);
}

void audio::gloria_song() {
	this->Beep(D5, full); //RE
	this->Beep(G5, full); //SOL
	this->sleep(half / 8);
	this->Beep(G5, full * 3 / 2); //SOL
	this->Beep(Gb5, full * 1 / 2); //FA#
	this->Beep(G5, full); //SOL
	this->Beep(B5, full); //SI
	this->sleep(half / 8);
	this->Beep(B5, full); //SI
	this->Beep(A5, full); //LA
	this->Beep(D6, full); //RE
	this->sleep(half / 8);
	this->Beep(D6, full); //RE
	this->sleep(half / 8);
	this->Beep(D6, full * 3 / 2); //RE
	this->Beep(C6, full * 1 / 2); //DO
	this->Beep(B5, full); //SI
	this->Beep(A5, full); //LA
	this->Beep(B5, full * 2); //SI
	this->Beep(D5, full); //RE
	this->sleep(half / 4);
	this->Beep(G5, full); //SOL
	this->sleep(half / 8);
	this->Beep(G5, full * 3 / 2); //SOL
	this->Beep(Gb5, full * 1 / 2); //FA#
	this->Beep(G5, full); //SOL
	this->Beep(B5, full); //SI
	this->sleep(half / 8);
	this->Beep(B5, full); //SI
	this->Beep(A5, full); //LA
	this->Beep(D6, full); //RE
	this->Beep(A5, full); //LA
	this->sleep(half / 8);
	this->Beep(A5, full * 3 / 2); //LA
	this->Beep(G5, full * 1 / 2); //SOL
	this->Beep(Gb5, full); //FA#
	this->Beep(E5, full); //MI
	this->Beep(D5, full * 2); //RE
	this->Beep(D6, full); //RE
	this->sleep(half / 8);
	this->Beep(D6, full); //RE
	this->sleep(half / 8);
	this->Beep(D6, full * 3 / 2); //RE
	this->Beep(G5, full * 1 / 2); //SOL
	this->Beep(C6, full); //DO
	this->Beep(B5, full); //SI
	this->sleep(half / 8);
	this->Beep(B5, full); //SI
	this->Beep(A5, full); //LA
	this->Beep(D6, full); //RE
	this->sleep(half / 8);
	this->Beep(D6, full); //RE
	this->sleep(half / 8);
	this->Beep(D6, full * 3 / 2); //RE
	this->Beep(G5, full * 1 / 2); //SOL
	this->Beep(C6, full); //DO
	this->Beep(B5, full); //SI
	this->Beep(A5, full * 2); //LA
	this->Beep(E6, full); //MI
	this->sleep(half / 8);
	this->Beep(E6, full); //MI
	this->sleep(half / 8);
	this->Beep(E6, full * 3 / 2); //MI
	this->Beep(D6, full * 1 / 2); //RE
	this->Beep(C6, full); //DO
	this->Beep(B5, full); //SI
	this->Beep(C6, full * 2); //DO
	this->sleep(half / 4);
	this->Beep(A5, full); //LA
	this->Beep(B5, full / 2); //SI
	this->Beep(C6, full / 2); //DO
	this->Beep(D6, full * 3 / 2); //RE
	this->Beep(G5, full * 1 / 2); //SOL
	this->sleep(half / 8);
	this->Beep(G5, full); //SOL
	this->Beep(A5, full); //LA
	this->Beep(B5, full * 2); //SI
	this->Beep(E6, full); //MI
	this->sleep(half / 8);
	this->Beep(E6, full); //MI
	this->sleep(half / 8);
	this->Beep(E6, full * 3 / 2); //MI
	this->Beep(D6, full / 1 / 2); //RE
	this->Beep(C6, full); //DO
	this->Beep(B5, full); //SI
	this->Beep(C6, full * 2); //DO
	this->sleep(half / 4);
	this->Beep(A5, full); //LA
	this->Beep(B5, full / 2); //SI
	this->Beep(C6, full / 2); //DO
	this->Beep(D6, full * 3 / 2); //RE
	this->Beep(G5, full * 1 / 2); //SOL
	this->sleep(half / 8);
	this->Beep(G5, full); //SOL
	this->Beep(Gb5, full); //FA#
	this->Beep(G5, full * 2); //SOL

	this->set_frequency(200000);
}

void audio::tetris_song() {
	this->Beep(658, 125);
	this->Beep(1320, 500);
	this->Beep(990, 250);
	this->Beep(1056, 250);
	this->Beep(1188, 250);
	this->Beep(1320, 125);
	this->Beep(1188, 125);
	this->Beep(1056, 250);
	this->Beep(990, 250);
	this->Beep(880, 500);
	this->Beep(880, 250);
	this->Beep(1056, 250);
	this->Beep(1320, 500);
	this->Beep(1188, 250);
	this->Beep(1056, 250);
	this->Beep(990, 750);
	this->Beep(1056, 250);
	this->Beep(1188, 500);
	this->Beep(1320, 500);
	this->Beep(1056, 500);
	this->Beep(880, 500);
	this->Beep(880, 500);
	this->sleep(250);
	this->Beep(1188, 500);
	this->Beep(1408, 250);
	this->Beep(1760, 500);
	this->Beep(1584, 250);
	this->Beep(1408, 250);
	this->Beep(1320, 750);
	this->Beep(1056, 250);
	this->Beep(1320, 500);
	this->Beep(1188, 250);
	this->Beep(1056, 250);
	this->Beep(990, 500);
	this->Beep(990, 250);
	this->Beep(1056, 250);
	this->Beep(1188, 500);
	this->Beep(1320, 500);
	this->Beep(1056, 500);
	this->Beep(880, 500);
	this->Beep(880, 500);
	this->sleep(500);
	this->Beep(1320, 500);
	this->Beep(990, 250);
	this->Beep(1056, 250);
	this->Beep(1188, 250);
	this->Beep(1320, 125);
	this->Beep(1188, 125);
	this->Beep(1056, 250);
	this->Beep(990, 250);
	this->Beep(880, 500);
	this->Beep(880, 250);
	this->Beep(1056, 250);
	this->Beep(1320, 500);
	this->Beep(1188, 250);
	this->Beep(1056, 250);
	this->Beep(990, 750);
	this->Beep(1056, 250);
	this->Beep(1188, 500);
	this->Beep(1320, 500);
	this->Beep(1056, 500);
	this->Beep(880, 500);
	this->Beep(880, 500);
	this->sleep(250);
	this->Beep(1188, 500);
	this->Beep(1408, 250);
	this->Beep(1760, 500);
	this->Beep(1584, 250);
	this->Beep(1408, 250);
	this->Beep(1320, 750);
	this->Beep(1056, 250);
	this->Beep(1320, 500);
	this->Beep(1188, 250);
	this->Beep(1056, 250);
	this->Beep(990, 500);
	this->Beep(990, 250);
	this->Beep(1056, 250);
	this->Beep(1188, 500);
	this->Beep(1320, 500);
	this->Beep(1056, 500);
	this->Beep(880, 500);
	this->Beep(880, 500);
	this->sleep(500);
	this->Beep(660, 1000);
	this->Beep(528, 1000);
	this->Beep(594, 1000);
	this->Beep(495, 1000);
	this->Beep(528, 1000);
	this->Beep(440, 1000);
	this->Beep(419, 1000);
	this->Beep(495, 1000);
	this->Beep(660, 1000);
	this->Beep(528, 1000);
	this->Beep(594, 1000);
	this->Beep(495, 1000);
	this->Beep(528, 500);
	this->Beep(660, 500);
	this->Beep(880, 1000);
	this->Beep(838, 2000);
	this->Beep(660, 1000);
	this->Beep(528, 1000);
	this->Beep(594, 1000);
	this->Beep(495, 1000);
	this->Beep(528, 1000);
	this->Beep(440, 1000);
	this->Beep(419, 1000);
	this->Beep(495, 1000);
	this->Beep(660, 1000);
	this->Beep(528, 1000);
	this->Beep(594, 1000);
	this->Beep(495, 1000);
	this->Beep(528, 500);
	this->Beep(660, 500);
	this->Beep(880, 1000);
	this->Beep(838, 2000);

	this->set_frequency(200000);
}

audio::~audio() {
	// TODO Auto-generated destructor stub
}

