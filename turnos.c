#include "turnos.h"
#include <stdio.h>

static void set_error(char *err_msg, size_t err_cap, const char *msg) {
    if (err_msg == NULL || err_cap == 0) return;
    if (msg == NULL) msg = "";
    snprintf(err_msg, err_cap, "%s", msg);
}

static void log_si(const TurnoDevolucion *dev, void *juego, int jugador_id, const char *evento) {
    if (dev != NULL && dev->log_evento != NULL) {
        dev->log_evento(juego, jugador_id, evento);
    }
}

void turnos_iniciar_turno(TurnoActual *turno, int jugador_id) {
    if (turno == NULL) return;

    turno->jugador_id = jugador_id;
    turno->acciones_consumidas = 0;
    turno->turno_finalizado = false;
}

TurnoEstado turnos_aplicar_comando(
    TurnoActual *turno,
    void *juego,
    const TurnoDevolucion *dev,
    const TurnoComando *cmd,
    char *err_msg,
    size_t err_cap
) {
    if (turno == NULL || dev == NULL || cmd == NULL) {
        set_error(err_msg, err_cap, "Parámetros inválidos.");
        return TURNO_SIGUE;
    }

    if (dev->intentar_mover == NULL ||
        dev->intentar_usar_dispositivo == NULL ||
        dev->juego_terminado == NULL) {
        set_error(err_msg, err_cap, "Retorno incompleto.");
        return TURNO_SIGUE;
    }

    if (dev->juego_terminado(juego)) {
        return JUEGO_TERMINO;
    }

    if (turno->turno_finalizado || turno->acciones_consumidas >= 2) {
        return TURNO_TERMINO;
    }

    if (cmd->tipo == ACCION_RENDIRSE) {
        log_si(dev, juego, turno->jugador_id, "RENDIRSE");
        return JUEGO_TERMINO;
    }

    if (cmd->tipo == ACCION_USAR_DISPOSITIVO) {
        char local_err[256];
        bool ok = dev->intentar_usar_dispositivo(
            juego,
            turno->jugador_id,
            cmd->dispositivo_id,
            local_err,
            sizeof(local_err)
        );

        if (!ok) {
            set_error(err_msg, err_cap, local_err);
            log_si(dev, juego, turno->jugador_id, "USAR_DISPOSITIVO_FALLA");
            return TURNO_SIGUE;
        }

        turno->acciones_consumidas++;
        log_si(dev, juego, turno->jugador_id, "USAR_DISPOSITIVO_OK");

        if (dev->juego_terminado(juego)) return JUEGO_TERMINO;

        if (turno->acciones_consumidas >= 2) {
            turno->turno_finalizado = true;
            return TURNO_TERMINO;
        }

        return TURNO_SIGUE;
    }

    if (cmd->tipo == ACCION_MOVER) {
        char local_err[256];
        bool ok = dev->intentar_mover(
            juego,
            turno->jugador_id,
            cmd->x_dest,
            cmd->y_dest,
            local_err,
            sizeof(local_err)
        );

        if (!ok) {
            set_error(err_msg, err_cap, local_err);
            log_si(dev, juego, turno->jugador_id, "MOVER_FALLA");
            return TURNO_SIGUE;
        }

        turno->acciones_consumidas++;
        turno->turno_finalizado = true;
        log_si(dev, juego, turno->jugador_id, "MOVER_OK");

        if (dev->juego_terminado(juego)) return JUEGO_TERMINO;

        return TURNO_TERMINO;
    }

    set_error(err_msg, err_cap, "Acción inválida.");
    return TURNO_SIGUE;
}
