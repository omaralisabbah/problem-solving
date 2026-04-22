/*
    An intelligent computing cluster innovatively adopts OXC (optical circuit switch) as the core layer to enable ultra-large-scale interconnection for tens of thousands of computing cards.

While OXC demonstrates advantages in latency, power efficiency, and bandwidth compared to electrical switches, its switching capability degrades from all-to-all to one-to-one. This makes it challenging to fully utilize OXC bandwidth.

Please develop a strategy to determine the optimal OXC configuration and routing schemes in response to AI tasks in real-time.

All links appearing in this problem can be considered as bidirectional edges.

What is OXC?

OXC can freely establish an optical connection between ports by rotating micro-mirrors to reflect light. An OXC optical connection refers to a connection between one internal port and another internal port of the OXC, forming a bidirectional pathway.

In the illustrated OXC, one optical connection is established between ports 0 and 2, while another connects ports 1 and 4. This allows the device connected to port 0 to have a communication link with the device connected to port 2, and similarly for ports 1 and 4. Note that optical connections are one-to-one!

In the network scenario shown in the figure above, OXC #0 establishes an optical connection between port 0 and port 2, creating a communication link between Spine #0 and Spine #1. By establishing an optical connection between port 1 and port 5, it creates a communication link between Spine #0 and Spine #2.


Overview of Two-Tier Electrical and One-Tier Optical Network

A Group contains two tiers of electrical switches (referred to as Leaf and Spine, as shown in the figure) and several NPUs (Neural Processing Units). Communication between NPUs within a Group can be completed solely through the electrical switches.

The OXC is only used to route traffic between different Groups. Such traffic is transmitted via the following path: NPU – Leaf – Spine – OXC – Spine – Leaf – NPU.

For each Spine, let Up
 be the number of links to OXCs and Down
 be the number of links to Leaves. We define the convergence ratio as Up:Down
. It is guaranteed that this ratio is 1:1
, 1:3
, or 1:7
.

Introduction to Multi-Plane Network

Spines and OXCs are divided into several independent plane sets (in the industry, this is done to scale the network size).
In each plane, between each Spine and each OXC belonging to this plane, there are exactly K
 links.
There are no links between Spines and OXCs in different planes.
Within each Group, there is exactly one physical link between each Leaf and each Spine.
Specific Network Description

There are N
 Groups numbered from 0
 to N−1
.
There are M
 OXCs numbered from 0
 to M−1
. OXC number i
 belongs to the plane numbered ⌊iM/P⌋
.
Each Group has S
 Spines numbered from 0
 to S−1
. Spine number i
 belongs to the plane numbered ⌊iS/P⌋
.
Each Group has L
 Leaves, numbered from 0
 to L−1
.
Within the same plane, each OXC and each Spine have exactly K
 links, numbered from 0
 to K−1
.
There are P
 planes numbered from 0
 to P−1
. The number of OXCs M
 and the number of Spines S
 are both divisible by P
.
From this, it follows that the number of ports per OXC is R=N⋅(S/P)⋅K
. The ports of each OXC are numbered from 0
 to R−1
.
The port corresponding to OXC number m
, Group number i
, Spine number j
, and link number k
 has the number i⋅(S/P)⋅K+(jmod(S/P))⋅K+k
.

For OXC number m
, port number i
 corresponds to Group number ⌊i(S/P)⋅K⌋
, Spine number imod((S/P)⋅K)K+⌊mM/P⌋⋅(S/P)
, and link number (imodK)
.

Leaf-Level Communication Flow Demand

Each AI task has different communication requirements between NPU cards. For simplicity, details such as NPU – Leaf connections are abstracted away in this problem.

Specifically, each query can be considered as several bidirectional flows. Each flow goes between some two leaves, LeafA and LeafB.

A flow is transmitted via a bidirectional path: LeafA – SpineA – OXC – SpineB – LeafB. It is guaranteed that, for all given flows, the Group numbers of LeafA and LeafB are different.

Now it is required to assign routes to all flows. We define the maximum flow conflict as the maximum number of flows passing through any link in the network.

Minimize the maximum flow conflict as much as possible.

OXC Physical Topology Adjustment

The OXC can freely adjust its physical topology, but adjustments incur overhead.

We define the OXC adjustment cost as a kind of edit distance between the target physical topology and the current physical topology. Specifically, we adjust an OXC by performing the following actions, each of which has a cost of 1
:

Establish a new connection between a pair of ports.
Remove an existing connection between a pair of ports.
Minimize the OXC adjustment cost as much as possible.

Initially, before any queries, no ports of any OXC have established connections. Before each query after the first one, the physical topology is exactly as it was after the previous query.

Here is an example of edit distance calculation:

Original topology: Port 1 is connected to port 2, port 0 is idle and unconnected.
New topology: Port 1 is connected to port 0, port 2 is idle and unconnected.
Removing the connection between port 1 and port 2, and establishing the connection between port 1 and port 0, results in an OXC adjustment cost of 2.
Input
The first line contains three positive integers N
, S
, and L
, representing the number of Groups, the number of Spines per Group, and the number of Leaves per Group, respectively (2≤N≤25
; 1≤S≤25
; 1≤L≤26
; additionally, 2≤N⋅S⋅L≤214
).

The second line contains three positive integers M
, K
, and P
, representing the number of OXCs, the number of links between each OXC and each Spine within the same plane, and the number of planes (1≤M≤28
; 1≤K≤2
; 1≤P≤24
).

Then five queries are given. For each query, the input format is as follows:

The first line of a description contains a positive integer Q
, indicating the number of bidirectional flow demands (1≤Q≤12(N⋅S⋅L)
).
Each of the next Q
 lines describes a bidirectional flow demand between LeafA and LeafB. The i
-th line, representing the i
-th bidirectional flow demand, contains four integers, in order:
gA
, number of Group of LeafA
LeafA number
gB
, number of Group of LeafB
LeafB number
The group numbers satisfy 0≤gA<gB≤N−1
, and the leaf numbers are from 0
 to L−1
.

It is guaranteed that S
 and M
 are divisible by P
, and that N−1≤S⋅(M/P)⋅K
.

It is guaranteed that the convergence ratio (M/P)⋅KL
 is either 1:1
 or 1:3
 or 1:7
.

It is guaranteed that each leaf appears no more than S
 times in each query.

Output
For each query, the output format is as follows:

First, output M
 lines. The i
-th line (0≤i≤M−1
) should contain R=N⋅(S/P)⋅K
 integers, representing the port connection relationships of OXC number i
. The j
-th integer vj
 (0≤j≤R−1
) indicates that the j
-th port of this OXC is connected to the vj
-th port. If vj
 is −1
, the port is idle.
Then output Q
 lines. For the i
-th line (0≤i≤Q−1
), output the planned routing path for the i
-th flow demand, containing five integers, in order:
Spine number x
 (0≤x<S
) connected to LeafA
Link number kx
 (0≤kx<K
) of x
 connected to the OXC
OXC number m
 (0≤m<M
)
Spine number y
 (0≤y<S
) connected to LeafB
Link number ky
 (0≤ky<K
) of y
 connected to the OXC
Scoring
Maximize the score as much as possible.

SCORE=∑all tests∑all queriesαmaximum flow conflict⋅convergence ratio+β⋅(1−OXC adjustment costM⋅R)

Where α=1000
 and β=300
.


Example
Input
2 1 2
2 1 1
2
0 1 1 0
0 0 1 1
2
0 0 1 0
0 1 1 1
2
0 1 1 0
0 0 1 1
2
0 0 1 0
0 1 1 1
2
0 0 1 0
0 1 1 1


Output
1 0 
1 0 
0 0 1 0 0
0 0 0 0 0
1 0 
1 0 
0 0 1 0 0
0 0 0 0 0
1 0 
1 0 
0 0 1 0 0
0 0 0 0 0
1 0 
1 0 
0 0 1 0 0
0 0 0 0 0
1 0 
1 0 
0 0 1 0 0
0 0 0 0 0


*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, S, L;
    if (!(cin >> N >> S >> L)) return 0;
    int M, K, P;
    cin >> M >> K >> P;

    const int spinesPerPlane = S / P;
    const int oxcsPerPlane   = M / P;
    const int R = N * spinesPerPlane * K; // ports per OXC

    auto planeOfOXC = [&](int m) -> int { return (m * P) / M; };
    auto oxcInPlane = [&](int p, int idx) -> int { return p * oxcsPerPlane + idx; };
    auto planeBaseSpine = [&](int p) -> int { return p * spinesPerPlane; };

    auto portIndex = [&](int /*m*/, int g, int jGlobal, int k) -> int {
        int p = (jGlobal * P) / S;
        int jLocal = jGlobal - planeBaseSpine(p);           // 0..spinesPerPlane-1
        return g * (spinesPerPlane * K) + jLocal * K + k;   // 0..R-1
    };

    // Round-robin starting offsets to spread load
    vector<vector<int>> rrLink(N, vector<int>(S, 0));
    vector<int> rrSpineOffsetA(P, 0), rrSpineOffsetB(P, 0);
    vector<int> rrOxcOffset(P, 0);

    for (int qid = 0; qid < 5; ++qid) {
        int Q; cin >> Q;
        struct Flow { int gA, A, gB, B; };
        vector<Flow> flows(Q);
        for (int i = 0; i < Q; ++i) cin >> flows[i].gA >> flows[i].A >> flows[i].gB >> flows[i].B;

        // Fresh topology for this query
        vector<vector<int>> oxc(M, vector<int>(R, -1));
        vector<vector<char>> used(M, vector<char>(R, 0));

        struct Route { int x, kx, m, y, ky; };
        vector<Route> routes(Q);

        auto tryPlace = [&](int gA, int A, int gB, int B, Route &route) -> bool {
            // Iterate planes: start from hash, then others
            vector<int> planes(P);
            int startP = (gA + gB) % P;
            iota(planes.begin(), planes.end(), 0);
            rotate(planes.begin(), planes.begin() + startP, planes.end());

            for (int p : planes) {
                // Candidate spines in plane p for A and B
                vector<int> spinesA(spinesPerPlane), spinesB(spinesPerPlane);
                int base = planeBaseSpine(p);
                for (int i = 0; i < spinesPerPlane; ++i) spinesA[i] = base + i;
                for (int i = 0; i < spinesPerPlane; ++i) spinesB[i] = base + i;
                // Rotate to vary starting point based on leaf id and rr offsets
                rotate(spinesA.begin(), spinesA.begin() + ((A + rrSpineOffsetA[p]) % spinesPerPlane), spinesA.end());
                rotate(spinesB.begin(), spinesB.begin() + ((B + rrSpineOffsetB[p]) % spinesPerPlane), spinesB.end());

                // Candidate OXCs in this plane
                vector<int> oxcs(oxcsPerPlane);
                for (int i = 0; i < oxcsPerPlane; ++i) oxcs[i] = oxcInPlane(p, i);
                rotate(oxcs.begin(), oxcs.begin() + rrOxcOffset[p], oxcs.end());

                for (int x : spinesA) {
                    for (int y : spinesB) {
                        // Try OXCs and links
                        for (int m : oxcs) {
                            if (planeOfOXC(m) != p) continue;
                            // Try all link pairs
                            for (int dx = 0; dx < K; ++dx) {
                                int kx = (rrLink[gA][x] + dx) % K;
                                int portA = portIndex(m, gA, x, kx);
                                if (used[m][portA]) continue;
                                for (int dy = 0; dy < K; ++dy) {
                                    int ky = (rrLink[gB][y] + dy) % K;
                                    int portB = portIndex(m, gB, y, ky);
                                    if (used[m][portB]) continue;

                                    // Place bidirectional connection
                                    oxc[m][portA] = portB;
                                    oxc[m][portB] = portA;
                                    used[m][portA] = 1;
                                    used[m][portB] = 1;

                                    // Record and advance RR
                                    route = {x, kx, m, y, ky};
                                    rrLink[gA][x] = (kx + 1) % K;
                                    rrLink[gB][y] = (ky + 1) % K;
                                    rrSpineOffsetA[p] = (rrSpineOffsetA[p] + 1) % spinesPerPlane;
                                    rrSpineOffsetB[p] = (rrSpineOffsetB[p] + 1) % spinesPerPlane;
                                    rrOxcOffset[p]     = (rrOxcOffset[p] + 1) % oxcsPerPlane;
                                    return true;
                                }
                            }
                        }
                    }
                }
            }
            return false; // No feasible free pair found (unlikely under given constraints)
        };

        for (int i = 0; i < Q; ++i) {
            Route r{};
            bool ok = tryPlace(flows[i].gA, flows[i].A, flows[i].gB, flows[i].B, r);
            if (!ok) {
                // As a last resort, place on first plane/first OXC with first free ports (guarded)
                bool forced = false;
                for (int p = 0; p < P && !forced; ++p) {
                    int base = planeBaseSpine(p);
                    for (int x = base; x < base + spinesPerPlane && !forced; ++x)
                        for (int y = base; y < base + spinesPerPlane && !forced; ++y)
                            for (int ioxc = 0; ioxc < oxcsPerPlane && !forced; ++ioxc) {
                                int m = oxcInPlane(p, ioxc);
                                for (int kx = 0; kx < K && !forced; ++kx) {
                                    int portA = portIndex(m, flows[i].gA, x, kx);
                                    if (used[m][portA]) continue;
                                    for (int ky = 0; ky < K && !forced; ++ky) {
                                        int portB = portIndex(m, flows[i].gB, y, ky);
                                        if (used[m][portB]) continue;
                                        oxc[m][portA] = portB;
                                        oxc[m][portB] = portA;
                                        used[m][portA] = 1;
                                        used[m][portB] = 1;
                                        r = {x, kx, m, y, ky};
                                        forced = true;
                                    }
                                }
                            }
                }
                if (!forced) {
                    // If truly impossible, output a trivial route (valid indices) with no OXC link changes
                    // But to stay correct, we must still connect: since constraints suggest enough capacity,
                    // reaching here should be exceedingly rare.
                    // For safety, connect on OXC 0 plane-compatible spines with k=0 if free.
                    cerr << "No feasible path found; constraints likely violated.\n";
                }
            }
            routes[i] = r;
        }

        // Output OXC topologies
        for (int m = 0; m < M; ++m) {
            for (int j = 0; j < R; ++j) {
                if (j) cout << ' ';
                cout << oxc[m][j];
            }
            cout << '\n';
        }
        // Output routes
        for (auto &r : routes) {
            cout << r.x << ' ' << r.kx << ' ' << r.m << ' ' << r.y << ' ' << r.ky << '\n';
        }
    }
    return 0;
}