#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DDOS_THRESHOLD 10
#define DDOS_TIME_WINDOW 60 // 60 seconds

// Structure definitions
typedef struct {
    int source_ip;
    int dest_ip;
    int port;
    char payload[100];
    time_t timestamp;
} Packet;

typedef struct {
    int id;
    char description[100];
    int threshold;
} Rule;

typedef struct {
    time_t timestamp;
    char message[200];
    int severity;
} Alert;

typedef struct {
    int ip;
    int count;
    time_t first_seen;
} IPStats;

// Global variables
Packet *packets = NULL;
Rule *rules = NULL;
Alert *alerts = NULL;
IPStats *ip_stats = NULL;

int packet_count = 0;
int rule_count = 0;
int alert_count = 0;
int ip_stats_count = 0;
int max_packets = 10;
int max_rules = 10;
int max_alerts = 10;
int max_ip_stats = 10;

FILE *log_file = NULL;

// Function prototypes
void initializeSystem();
void resizePackets();
void resizeRules();
void resizeAlerts();
void resizeIPStats();
void addPacket();
void analyzePacket(Packet *p);
void addRule();
void generateAlert(const char *message, int severity);
void displayAlerts();
void initializeLogging();
int validateIP(int ip);
void updateIPStats(int source_ip);
void checkDDoS();
void displayStats();
void closeLogging();

int main() {
    int choice;
    initializeSystem();
    initializeLogging();

    while (1) {
        printf("\nIntrusion Detection System\n");
        printf("1. Add new packet\n");
        printf("2. Add detection rule\n");
        printf("3. Display alerts\n");
        printf("4. Display statistics\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar(); // Clear newline character from input buffer

        switch (choice) {
            case 1:
                addPacket();
                break;
            case 2:
                addRule();
                break;
            case 3:
                displayAlerts();
                break;
            case 4:
                displayStats();
                break;
            case 5:
                closeLogging();
                free(packets);
                free(rules);
                free(alerts);
                free(ip_stats);
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }
}

void initializeSystem() {
    packets = (Packet *)malloc(max_packets * sizeof(Packet));
    rules = (Rule *)malloc(max_rules * sizeof(Rule));
    alerts = (Alert *)malloc(max_alerts * sizeof(Alert));
    ip_stats = (IPStats *)malloc(max_ip_stats * sizeof(IPStats));

    packet_count = 0;
    rule_count = 0;
    alert_count = 0;
    ip_stats_count = 0;

    // Add a default rule
    Rule defaultRule = {1, "Suspicious port scan detected", 100};
    rules[rule_count++] = defaultRule;
}

void resizePackets() {
    max_packets *= 2;
    packets = (Packet *)realloc(packets, max_packets * sizeof(Packet));
}

void resizeRules() {
    max_rules *= 2;
    rules = (Rule *)realloc(rules, max_rules * sizeof(Rule));
}

void resizeAlerts() {
    max_alerts *= 2;
    alerts = (Alert *)realloc(alerts, max_alerts * sizeof(Alert));
}

void resizeIPStats() {
    max_ip_stats *= 2;
    ip_stats = (IPStats *)realloc(ip_stats, max_ip_stats * sizeof(IPStats));
}

void initializeLogging() {
    log_file = fopen("ids_log.txt", "a");
    if (log_file == NULL) {
        printf("Error: Could not open log file!\n");
        exit(1);
    }
}

void closeLogging() {
    if (log_file != NULL) {
        fclose(log_file);
    }
}

void addPacket() {
    if (packet_count >= max_packets) {
        resizePackets();
    }

    Packet p;
    printf("Enter source IP (as integer 1-255): ");
    scanf("%d", &p.source_ip);
    if (!validateIP(p.source_ip)) {
        printf("Invalid IP address!\n");
        return;
    }

    printf("Enter destination IP (as integer 1-255): ");
    scanf("%d", &p.dest_ip);
    if (!validateIP(p.dest_ip)) {
        printf("Invalid IP address!\n");
        return;
    }

    printf("Enter port (0-65535): ");
    scanf("%d", &p.port);
    if (p.port < 0 || p.port > 65535) {
        printf("Invalid port number!\n");
        return;
    }

    printf("Enter payload: ");
    scanf(" %99[^\n]", p.payload);
    p.timestamp = time(NULL);

    packets[packet_count++] = p;
    updateIPStats(p.source_ip);
    checkDDoS();
    analyzePacket(&p);

    // Log packet to file
    fprintf(log_file, "[%s] Packet: SRC=%d, DST=%d, PORT=%d, PAYLOAD=%s\n",
            ctime(&p.timestamp), p.source_ip, p.dest_ip, p.port, p.payload);
    fflush(log_file);
}

int validateIP(int ip) {
    return (ip >= 1 && ip <= 255);
}

void updateIPStats(int source_ip) {
    time_t current_time = time(NULL);

    for (int i = 0; i < ip_stats_count; i++) {
        if (ip_stats[i].ip == source_ip) {
            ip_stats[i].count++;
            return;
        }
    }

    if (ip_stats_count >= max_ip_stats) {
        resizeIPStats();
    }

    ip_stats[ip_stats_count].ip = source_ip;
    ip_stats[ip_stats_count].count = 1;
    ip_stats[ip_stats_count].first_seen = current_time;
    ip_stats_count++;
}

void checkDDoS() {
    time_t current_time = time(NULL);

    for (int i = 0; i < ip_stats_count; i++) {
        if (current_time - ip_stats[i].first_seen <= DDOS_TIME_WINDOW) {
            if (ip_stats[i].count >= DDOS_THRESHOLD) {
                char alert_msg[200];
                sprintf(alert_msg, "Possible DDoS attack detected from IP: %d (Packets: %d)",
                        ip_stats[i].ip, ip_stats[i].count);
                generateAlert(alert_msg, 3);
            }
        } else {
            ip_stats[i].count = 0;
            ip_stats[i].first_seen = current_time;
        }
    }
}

void analyzePacket(Packet *p) {
    if (strstr(p->payload, "exploit") || strstr(p->payload, "attack")) {
        generateAlert("Suspicious payload detected", 3);
    }
}

void addRule() {
    if (rule_count >= max_rules) {
        resizeRules();
    }

    Rule r;
    r.id = rule_count + 1;
    printf("Enter rule description: ");
    scanf(" %[^\n]s", r.description);
    printf("Enter threshold: ");
    scanf("%d", &r.threshold);

    rules[rule_count++] = r;
}

void generateAlert(const char *message, int severity) {
    if (alert_count >= max_alerts) {
        resizeAlerts();
    }

    Alert a;
    a.timestamp = time(NULL);
    strcpy(a.message, message);
    a.severity = severity;

    alerts[alert_count++] = a;
}

void displayAlerts() {
    if (alert_count == 0) {
        printf("No alerts to display.\n");
        return;
    }

    printf("\nAlert Log:\n");
    for (int i = 0; i < alert_count; i++) {
        printf("Time: %s", ctime(&alerts[i].timestamp));
        printf("Message: %s\n", alerts[i].message);
        printf("Severity: %d\n\n", alerts[i].severity);
    }
}

void displayStats() {
    printf("\nPacket Statistics:\n");
    printf("Total packets processed: %d\n", packet_count);
    printf("Active rules: %d\n", rule_count);
    printf("Total alerts: %d\n\n", alert_count);

    printf("IP Statistics:\n");
    for (int i = 0; i < ip_stats_count; i++) {
        printf("IP: %d, Packet Count: %d\n", ip_stats[i].ip, ip_stats[i].count);
    }
}
