#pragma once
#ifndef __PENDULUMS_H__

#define __PENDULUMS_H__

#include <vector>
#include <cmath>
#include <string>

namespace pendulums{
//    const static double PI = 4*std::atan(1.0);
	const static double grav= 0.0;//9.8; // gravitational myacceleraion
//    using std::sin;
//    using std::cos;

	//pendState:     struct for variables for pendulums (mytheta x3, differential of mytheta x3)
	//pendStateDiff: struct for differential of pendState
    class pendStateDiffprim{
    public:
        double diff[6];
    };
//    class pendStateDiff:public pendStateDiffprim{};
	 class pendState{
     public:
		double mytheta[3];
		double dtheta[3];
        pendState(){
            mytheta[0] =20.*(float)std::rand()/(float)RAND_MAX;
             mytheta[1] = 3.5;
             mytheta[2] = 1.5;
             dtheta[0] = 0.8;
             dtheta[1] = 0.5;
             dtheta[2] = -9.0;
         }
         void addDiff(const pendState p, const pendStateDiffprim pd, double r){
             for(int i = 0; i < 3; i++){
                 mytheta[i] = p.mytheta[i] + r*pd.diff[i];
                 dtheta[i] = p.dtheta[i] + r*pd.diff[i+3];
             }
         }
         void myadjust(){
             for(int i = 0; i < 3; i++){
                 if(mytheta[i] < 0.0) mytheta[i] += 2*PI;
                 else if(mytheta[i] > 2*PI) mytheta[i] -= 2*PI;
             }
         }
	};
	class pendStateDiff:public pendStateDiffprim{
    public:
//        double diff[6];
        pendStateDiff(){};
        pendStateDiff(const pendState& p, const double myaccel[3], const double dt){
            for(int i = 0; i < 3; i++){
                diff[i] = dt*p.dtheta[i];
                diff[i+3] = dt*myaccel[i];
            }	};
    };

	class pendClass{

	public:
		pendClass(){
			length[0] = 0.4;
			length[1] = 0.5;
			length[2] = 0.8;
			mass[0] = 2.0;
			mass[1] = 2.0;
			mass[2] = 1.0;
			integrateMethod = 1;
		}

		void initialize(){
			pend = pendState();
		}

		void setIntegrate(int _integrateMethod){
			integrateMethod = _integrateMethod;
		}

		std::string getIntegrateName(){
			switch(integrateMethod){
			case 1:
				return "Euler Method";
			case 2:
				return "Heun's Method";
			case 3:
				return "Runge-Kutta Method";
			default:
				return "Unknown";
			}
		}

		//return vertices of pendulums (contains 4 pairs)
		std::vector<std::pair<double, double> > vertices(){
			std::vector<std::pair<double, double> > ans;
			std::pair<double, double> tmpV(0.0, 0.0);
			ans.push_back(tmpV);
			for(int i = 0; i < 3; i++){
				tmpV.first += length[i]*sin(pend.mytheta[i]);
				tmpV.second -= length[i]*cos(pend.mytheta[i]);
				ans.push_back(tmpV);
			}
			return ans;
		}

		double T(){ return calcT(pend);}
		double U(){ return calcU(pend);}
		double energy(){ return calcEnergy(pend);}

		void move(const double dt){
			//integrate
			switch(integrateMethod){
			case 1:
				integrate_euler(dt);
				break;
			case 2:
				integrate_heun(dt);
				break;
			case 3:
				integrate_runge_kutta(dt);
				break;
			}
			//0 < mytheta < 2*PI
			pend.myadjust();
		}

	private:
        pendState pend;
        double length[3];
        double mass[3];
        int integrateMethod;
		void integrate_euler(const double dt){
			double myaccel[3];
			calcAccel(pend, myaccel);
			pendStateDiff k1(pend, myaccel, dt);

			pend.addDiff(pend, k1, 1.0);
		}

		void integrate_heun(const double dt){
			double myaccel[3];
			pendState p1;
			calcAccel(pend, myaccel);
			pendStateDiff k1(pend, myaccel, dt);

			p1.addDiff(pend, k1, 1.0/2.0);
			calcAccel(p1, myaccel);
			pendStateDiff k2(p1, myaccel, dt);

			pendStateDiff k;
			for(int i = 0; i < 6; i++){
				k.diff[i] = 1.0/2.0*(k1.diff[i]+k2.diff[i]);
			}
			pend.addDiff(pend, k, 1.0);
		}

		void integrate_runge_kutta(const double dt){
			double myaccel[3];
			pendState p1, p2, p3;
			calcAccel(pend, myaccel);
			pendStateDiff k1(pend, myaccel, dt);

			p1.addDiff(pend, k1, 1.0/2.0);
			calcAccel(p1, myaccel);
			pendStateDiff k2(p1, myaccel, dt);

			p2.addDiff(pend, k2, 1.0/2.0);
			calcAccel(p2, myaccel);
			pendStateDiff k3(p2, myaccel, dt);

			p3.addDiff(pend, k3, 1.0);
			calcAccel(p3, myaccel);
			pendStateDiff k4(p3, myaccel, dt);

			pendStateDiff k;
			for(int i = 0; i < 6; i++){
				k.diff[i] = 1.0/6.0*(k1.diff[i]+2.0*k2.diff[i]+2.0*k3.diff[i]+k4.diff[i]);
			}
			pend.addDiff(pend, k, 1.0);
		}

		//calculation of generalized myacceleration
		void calcAccel(const pendState& p, double myaccel[3]){
			//set matrices
			double myaccelMat[3][3];
			myaccelMat[0][0] = 1.0/3.0*mass[0]+mass[1]+mass[2];
			myaccelMat[1][1] = 1.0/3.0*mass[1]+mass[2];
			myaccelMat[2][2] = 1.0/3.0*mass[2];
			myaccelMat[0][1] = myaccelMat[1][0] = (1.0/2.0*mass[1]+mass[2])*cos(p.mytheta[0] - p.mytheta[1]);
			myaccelMat[0][2] = myaccelMat[2][0] = 1.0/2.0*mass[2]*cos(p.mytheta[0] - p.mytheta[2]);
			myaccelMat[1][2] = myaccelMat[2][1] = 1.0/2.0*mass[2]*cos(p.mytheta[1] - p.mytheta[2]);

			double forceMat1[3][3];
			forceMat1[0][0] = forceMat1[1][1] = forceMat1[2][2] = 0.0;
			forceMat1[0][1] = -(1.0/2.0*mass[1]+mass[2])*sin(p.mytheta[0] - p.mytheta[1]);
			forceMat1[1][0] = -forceMat1[0][1];
			forceMat1[0][2] = -1.0/2.0*mass[2]*sin(p.mytheta[0] - p.mytheta[2]);
			forceMat1[2][0] = -forceMat1[0][2];
			forceMat1[1][2] = -1.0/2.0*mass[2]*sin(p.mytheta[1] - p.mytheta[2]);
			forceMat1[2][1] = -forceMat1[1][2];

			//set right value
			double forceVec[3];
			forceVec[0] = -(1.0/2.0*mass[0]+mass[1]+mass[2])* grav*sin(p.mytheta[0]);
			forceVec[1] = -(1.0/2.0*mass[1]+mass[2])* grav*sin(p.mytheta[1]);
			forceVec[2] = -(1.0/2.0*mass[2])* grav*sin(p.mytheta[2]);
			for(int i = 0; i < 3; i++){
				for(int j = 0; j < 3; j++){
					forceVec[i] += forceMat1[i][j] * length[j]*p.dtheta[j]*p.dtheta[j];
				}
			}

			//Gauss-Jordan  elimination
			for(int i = 0; i < 3; i++){
				double tmpElem = myaccelMat[i][i];
				forceVec[i] /= tmpElem;
				for(int k = i; k < 3; k++){
					myaccelMat[i][k] /= tmpElem;
				}
				for(int j = 0; j < 3; j++){
					if(i==j) continue;
					tmpElem = myaccelMat[j][i];
					forceVec[j] -= tmpElem*forceVec[i];
					for(int k = i; k < 3; k++){
						myaccelMat[j][k] -= tmpElem*myaccelMat[i][k];
					}
				}
			}

			for(int i = 0; i < 3; i++){
				myaccel[i] = forceVec[i] / length[i];
			}
		}

		//Kinetic Energy
		double calcT(const pendState& p){
			return (1.0/6.0*mass[0]+1.0/2.0*mass[1]+1.0/2.0*mass[2])*length[0]*length[0]*p.dtheta[0]*p.dtheta[0]
			     + (1.0/6.0*mass[1]+1.0/2.0*mass[2])                *length[1]*length[1]*p.dtheta[1]*p.dtheta[1]
			     + (1.0/6.0*mass[2])                                *length[2]*length[2]*p.dtheta[2]*p.dtheta[2]
			     + (1.0/2.0*mass[1]+mass[2])                        *length[0]*length[1]*p.dtheta[0]*p.dtheta[1]*cos(p.mytheta[0]-p.mytheta[1])
			     + (1.0/2.0*mass[2])                                *length[0]*length[2]*p.dtheta[0]*p.dtheta[2]*cos(p.mytheta[0]-p.mytheta[2])
			     + (1.0/2.0*mass[2])                                *length[1]*length[2]*p.dtheta[1]*p.dtheta[2]*cos(p.mytheta[1]-p.mytheta[2]);
		}

		//Potential Energy
		double calcU(const pendState& p){
			return - grav*(
				  (1.0/2.0*mass[0]+mass[1]+mass[2])*length[0]*(-1.0+cos(p.mytheta[0]))
				+ (1.0/2.0*mass[1]+mass[2])        *length[1]*(-1.0+cos(p.mytheta[1]))
				+ (1.0/2.0*mass[2])                *length[2]*(-1.0+cos(p.mytheta[2]))
				);
		}

		double calcEnergy(const pendState& p){
			return calcT(p)+calcU(p);
		}
	};
}

#endif
